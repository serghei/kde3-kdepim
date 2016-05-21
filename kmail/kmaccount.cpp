/************************************************************************\
 *
 *  kmail: KDE mail client
 *
 *  class KMAccount
 *
 *  (c) 1996-1998 Stefan Taferner <taferner@kde.org>
 *  (c) 2016 Serghei Amelian <serghei.amelian@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
\************************************************************************/
#include <config.h>

#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#include <qeventloop.h>

#include <kapplication.h>
#include <kconfig.h>
#include <kdebug.h>
#include <klocale.h>
#include <kmessagebox.h>

#include <libkpimidentities/identity.h>
#include <libkpimidentities/identitymanager.h>

#include "accountmanager.h"
#include "broadcaststatus.h"
#include "globalsettings.h"
#include "kmacctfolder.h"
#include "kmfiltermgr.h"
#include "kmfoldercachedimap.h"
#include "kmfoldermgr.h"
#include "kmmessage.h"
#include "messagesender.h"
#include "progressmanager.h"

#include "kmaccount.h"


using KMail::AccountManager;
using KMail::FolderJob;
using KPIM::BroadcastStatus;
using KPIM::ProgressItem;
using KPIM::ProgressManager;


KMPrecommand::KMPrecommand(const QString &precommand, QObject *parent)
    : QObject(parent)
    , mPrecommand(precommand)
{
    BroadcastStatus::instance()->setStatusMsg(i18n("Executing precommand %1").arg(precommand));

    mPrecommandProcess.setUseShell(true);
    mPrecommandProcess << precommand;

    connect(&mPrecommandProcess, SIGNAL(processExited(KProcess *)), SLOT(precommandExited(KProcess *)));
}


KMPrecommand::~KMPrecommand()
{
}


bool KMPrecommand::start()
{
    bool ok = mPrecommandProcess.start(KProcess::NotifyOnExit);

    if(!ok)
        KMessageBox::error(0, i18n("Could not execute precommand '%1'.").arg(mPrecommand));

    return ok;
}


void KMPrecommand::precommandExited(KProcess *p)
{
    int exitCode = (p->normalExit() ? p->exitStatus() : -1);

    if(exitCode)
        KMessageBox::error(0, i18n("The precommand exited with code %1:\n%2").arg(exitCode).arg(strerror(exitCode)));

    emit finished(!exitCode);
}



KMAccount::KMAccount(AccountManager *aOwner, const QString &aName, uint id)
    : KAccount(id, aName)
    , mTrash(KMKernel::self()->trashFolder()->idString())
    , mOwner(aOwner)
    , mFolder(0)
    , mTimer(this, "KMAccount::mTimer")
    , mTimerInstalled(false)
    , mTimerInterval(0)
    , mExclude(false)
    , mCheckingMail(false)
    , mPrecommandSuccess(true)
    , mHasInbox(false)
    , mMailCheckProgressItem(0)
    , mIdentityId(0)
{
    assert(aOwner != 0);

    connect(&mTimer, SIGNAL(timeout()), SLOT(mailCheck()));
}


void KMAccount::init()
{
    mTrash = kmkernel->trashFolder()->idString();
    mExclude = false;
    mTimerInterval = 0;
    mNewInFolder.clear();
}


KMAccount::~KMAccount()
{
    if((kmkernel && !kmkernel->shuttingDown()) && mFolder)
        mFolder->removeAccount(this);
}


void KMAccount::setFolder(KMFolder *folder, bool addAccount)
{
    if(!folder)
    {
        // kdDebug(5006) << "KMAccount::setFolder() : aFolder == 0" << endl;
        mFolder = 0;
        return;
    }

    mFolder = static_cast<KMAcctFolder*>(folder);

    if(addAccount)
        mFolder->addAccount(this);
}


void KMAccount::readConfig(KConfig &config)
{
    mFolder = nullptr;

    setCheckInterval(config.readNumEntry("check-interval", 0));
    setTrash(config.readEntry("trash", kmkernel->trashFolder()->idString()));
    setCheckExclude(config.readBoolEntry("check-exclude", false));
    setPrecommand(config.readPathEntry("precommand"));
    setIdentityId(config.readNumEntry("identity-id", 0));

    QString folderName = config.readEntry("Folder");
    if(!folderName.isEmpty())
        setFolder(kmkernel->folderMgr()->findIdString(folderName), true);

    readTimerConfig();
}


void KMAccount::readTimerConfig()
{
    // Re-reads and checks check-interval value and deinstalls timer incase check-interval
    // for mail check is disabled.
    // Or else, the mail sync goes into a infinite loop (kolab/issue2607)
    if(mTimerInterval)
        installTimer();
    else
        deinstallTimer();
}


void KMAccount::writeConfig(KConfig &config)
{
    // ID, Name
    KAccount::writeConfig(config);

    config.writeEntry("Type", type());
    config.writeEntry("Folder", mFolder ? mFolder->idString() : QString::null);
    config.writeEntry("check-interval", mTimerInterval);
    config.writeEntry("check-exclude", mExclude);
    config.writePathEntry("precommand", mPrecommand);
    config.writeEntry("trash", mTrash);

    if(mIdentityId && mIdentityId != kmkernel->identityManager()->defaultIdentity().uoid())
        config.writeEntry("identity-id", mIdentityId);
    else
        config.deleteEntry("identity-id");
}


void KMAccount::sendReceipt(KMMessage *msg)
{
    KConfig *config = KMKernel::config();
    KConfigGroup general(config, "General");
    bool sendReceipts = config->readBoolEntry("send-receipts", false);

    if(sendReceipts)
    {
        KMMessage *newMsg = msg->createDeliveryReceipt();
        if(newMsg)
        {
            mReceipts.append(newMsg);
            QTimer::singleShot(0, this, SLOT(sendReceipts()));
        }
    }
}


bool KMAccount::processNewMsg(KMMessage *msg)
{
    assert(msg != 0);

    // Save this one for readding
    KMFolderCachedImap *parent = nullptr;
    if(type() == "cachedimap")
        parent = static_cast<KMFolderCachedImap*>(msg->storage());

    // checks whether we should send delivery receipts
    // and sends them.
    sendReceipt(msg);

    // Set status of new messages that are marked as old to read, otherwise
    // the user won't see which messages newly arrived.
    // This is only valid for pop accounts and produces wrong status for imap.
    if(type() != "cachedimap" && type() != "imap")
    {
        if(msg->isOld())
            msg->setStatus(KMMsgStatusUnread);
        else
            msg->setStatus(KMMsgStatusNew);
    }

    // 0==message moved; 1==processing ok, no move; 2==critical error, abort!
    int processResult = kmkernel->filterMgr()->process(msg, KMFilterMgr::Inbound, true, id());

    switch(processResult)
    {
        case 1:
        {
            if(type() == "cachedimap")
            {
                // already done by caller: parent->addMsgInternal( aMsg, false );
            }
            else
            {
                // TODO: Perhaps it would be best, if this if was handled by a virtual
                // method, so the if( !dimap ) above could die?
                kmkernel->filterMgr()->tempOpenFolder(mFolder);
                int rc = mFolder->addMsg(msg);

                if(rc)
                {
                    perror("failed to add message");
                    KMessageBox::information(0, i18n("Failed to add message:\n%1").arg(strerror(rc)));
                    return false;
                }

                int count = mFolder->count();

                // If count == 1, the message is immediately displayed
                if(count != 1)
                    mFolder->unGetMsg(count - 1);
            }
            break;
        }

        case 2:
        {
            perror("Critical error: Unable to collect mail (out of space?)");
            KMessageBox::information(0, i18n("Critical error: Unable to collect mail: %1").arg(QString::fromLocal8Bit(strerror(errno))));
            return false;
        }
    }

    // Count number of new messages for each folder
    QString folderId;

    if(processResult == 1)
        folderId = (type() == "cachedimap") ? parent->folder()->idString() : mFolder->idString();
    else
        folderId = msg->parent()->idString();

    addToNewInFolder(folderId, 1);

    //Everything's fine - message has been added by filter  }
    return true;
}


void KMAccount::setCheckInterval(int newInterval)
{
    kdDebug(5006) << "KMAccount::setCheckInterval(newInterval: " << newInterval << ")" << endl;

    if(newInterval <= 0)
        mTimerInterval = 0;
    else
        mTimerInterval = newInterval;

    // Don't call installTimer from here! See #117935.
}


int KMAccount::checkInterval() const
{
    if(mTimerInterval <= 0)
        return mTimerInterval;

    return QMAX(mTimerInterval, GlobalSettings::self()->minimumCheckInterval());
}


void KMAccount::deleteFolderJobs()
{
    mJobList.setAutoDelete(true);
    mJobList.clear();
    mJobList.setAutoDelete(false);
}


void KMAccount::ignoreJobsForMessage(KMMessage *msg)
{
    //FIXME: remove, make folders handle those
    for(const auto &job : mJobList)
    {
        if(job->msgList().first() == msg)
        {
            mJobList.remove(job);
            delete job;
            break;
        }
    }
}


void KMAccount::setCheckExclude(bool aExclude)
{
    mExclude = aExclude;
}


void KMAccount::installTimer()
{
    kdDebug(5006) << "KMAccount::installTimer()" << endl;

    mTimerInstalled = true;
    mTimer.start(checkInterval() * 60000, true); // single shot
}


void KMAccount::deinstallTimer()
{
    kdDebug(5006) << "KMAccount::deinstallTimer()" << endl;

    mTimerInstalled = false;
    mTimer.stop();
}


bool KMAccount::runPrecommand(const QString &precommand)
{
    kdDebug(5006) << "KMAccount::runPrecommand(precommand: \"" << precommand << "\")" << endl;

    // Run the pre command if there is one
    if(precommand.isEmpty())
        return true;

    KMPrecommand precommandProcess(precommand, this);
    BroadcastStatus::instance()->setStatusMsg(i18n("Executing precommand %1").arg(precommand));
    connect(&precommandProcess, SIGNAL(finished(bool)), SLOT(precommandExited(bool)));

    if(!precommandProcess.start())
        return false;

    kapp->eventLoop()->enterLoop();

    return mPrecommandSuccess;
}


void KMAccount::precommandExited(bool success)
{
    mPrecommandSuccess = success;
    kapp->eventLoop()->exitLoop();
}


void KMAccount::mailCheck()
{
    kdDebug(5006) << "KMAccount::mailCheck()" << endl;

    if(kmkernel)
    {
        // stop the timer, maybe the mail check was
        // initiated manually by user
        mTimer.stop();

        AccountManager *accountManager = kmkernel->acctMgr();
        if(accountManager)
            accountManager->singleCheckMail(this, false);
    }
}


void KMAccount::sendReceipts()
{
    for(const auto &receipt : mReceipts)
        kmkernel->msgSender()->send(receipt); //might process events

    mReceipts.clear();
}


QString KMAccount::encryptStr(const QString &inStr)
{
    QString result;

    for(uint i = 0; i < inStr.length(); i++)
    {
        // yes, no typo. can't encode ' ' or '!' because
        // they're the unicode BOM. stupid scrambling. stupid.
        result += (inStr[i].unicode() <= 0x21) ? inStr[i] : QChar(0x1001F - inStr[i].unicode());
    }

    return result;
}


QString KMAccount::importPassword(const QString &str)
{
    int len = str.length();
    char result[len + 1];

    int i;

    for(i = 0; i < len; i++)
    {
        uchar val = str[i] - ' ';
        val = (255 - ' ') - val;
        result[i] = val + ' ';
    }

    result[i] = '\0';

    return encryptStr(result);
}


void KMAccount::invalidateIMAPFolders()
{
    // Default: Don't do anything. The IMAP account will handle it
}


void KMAccount::pseudoAssign(const KMAccount *account)
{
    if(!account)
        return;

    setName(account->name());
    setId(account->id());
    setCheckInterval(account->checkInterval());
    setCheckExclude(account->checkExclude());
    setFolder(account->folder());
    setPrecommand(account->precommand());
    setTrash(account->trash());
    setIdentityId(account->identityId());
}


void KMAccount::checkDone(bool newmail, CheckStatus status)
{
    kdDebug(5006) << "KMAccount::checkDone(newmail: " << newmail << ", status: " << status << ")" << endl;

    setCheckingMail(false);

    if(mTimerInstalled)
    {
        // start the timer again
        mTimer.start(checkInterval() * 60000, true); // one shot
    }

    if(mMailCheckProgressItem)
    {
        // set mMailCheckProgressItem = 0 before calling setComplete() to prevent
        // a race condition
        ProgressItem *savedMailCheckProgressItem = mMailCheckProgressItem;
        mMailCheckProgressItem = 0;
        savedMailCheckProgressItem->setComplete(); // that will delete it
    }

    emit newMailsProcessed(mNewInFolder);
    emit finishedCheck(newmail, status);
    mNewInFolder.clear();
}


void KMAccount::addToNewInFolder(QString folderId, int num)
{
    if(mNewInFolder.contains(folderId))
        mNewInFolder[folderId] += num;
    else
        mNewInFolder[folderId] = num;
}


#include "kmaccount.moc"
