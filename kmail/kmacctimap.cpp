/************************************************************************\
 *
 *  kmail: KDE mail client
 *
 *  class KMAcctImap
 *
 *  (c) 2000-2002 Michael Haeckel <haeckel@kde.org>
 *  (c) 2016 Serghei Amelian <serghei.amelian@gmail.com>
 *
 *  This file is based on popaccount.h by Don Sanders
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

#include <errno.h>

#include <qstylesheet.h>

#include <kdebug.h>
#include <kio/scheduler.h>
#include <kio/slave.h>
#include <kmessagebox.h>

#include "actionscheduler.h"
#include "broadcaststatus.h"
#include "folderstorage.h"
#include "imapjob.h"
#include "kmfilter.h"
#include "kmfiltermgr.h"
#include "kmfolderimap.h"
#include "kmfoldermgr.h"
#include "kmfoldertree.h"
#include "kmmainwin.h"
#include "kmmessage.h"
#include "kmmsgdict.h"
#include "progressmanager.h"


using KMail::ActionScheduler;
using KMail::ImapAccountBase;
using KMail::ImapJob;
using KMail::SieveConfig;
using KPIM::BroadcastStatus;
using KPIM::ProgressItem;
using KPIM::ProgressManager;


#include "kmacctimap.h"


KMAcctImap::KMAcctImap(AccountManager *owner, const QString &accountName, uint id)
    : KMail::ImapAccountBase(owner, accountName, id)
    , mFolder(nullptr)
    , mCountRemainChecks(0)
    , mErrorTimer(this, "KMAcctImap::mErrorTimer")
    , mScheduler(nullptr)
{
    mOpenFolders.setAutoDelete(true);

    QString serNumUri = locateLocal("data", QString("kmail/unfiltered.%1").arg(KAccount::id()));
    KConfig config(serNumUri);
    QStringList serNums = config.readListEntry("unfiltered");

    for(const auto &serNum : serNums)
    {
        mFilterSerNums.append(serNum.toUInt());
        mFilterSerNumsToSave.insert(serNum, 1);
    }

    connect(kmkernel->imapFolderMgr(), SIGNAL(changed()), this, SLOT(slotUpdateFolderList()));
    connect(&mErrorTimer, SIGNAL(timeout()), SLOT(slotResetConnectionError()));

    mNoopTimer.start(60000); // send a noop every minute
}


KMAcctImap::~KMAcctImap()
{
    killAllJobs(true);

    QString serNumUri = locateLocal("data", QString("kmail/unfiltered.%1").arg(KAccount::id()));
    KConfig config(serNumUri);
    config.writeEntry("unfiltered", mFilterSerNumsToSave.keys());
}


void KMAcctImap::pseudoAssign(const KMAccount *account)
{
    killAllJobs(true);

    if(mFolder)
    {
        mFolder->setContentState(KMFolderImap::imapNoInformation);
        mFolder->setSubfolderState(KMFolderImap::imapNoInformation);
    }

    ImapAccountBase::pseudoAssign(account);
}


void KMAcctImap::setImapFolder(KMFolderImap *folder)
{
    mFolder = folder;
    mFolder->setImapPath("/");
}


bool KMAcctImap::handleError(int errorCode, const QString &errorMsg, KIO::Job *job, const QString &context, bool abortSync)
{
    /* TODO check where to handle this one better. */
    if(errorCode == KIO::ERR_DOES_NOT_EXIST)
    {
        // folder is gone, so reload the folderlist
        if(mFolder)
            mFolder->listDirectory();

        return true;
    }

    return ImapAccountBase::handleError(errorCode, errorMsg, job, context, abortSync);
}


void KMAcctImap::killAllJobs(bool disconnectSlave)
{
    kdDebug(5006) << "KMAcctImap::killAllJobs(disconnectSlave: " << disconnectSlave << ")" << endl;

    for(const auto &job : mapJobData)
    {
        for(const auto &msg : job.msgList)
        {
            if(msg->transferInProgress())
            {
                kdDebug(5006) << "   msg->setTransferInProgress(false)" << endl;
                msg->setTransferInProgress(false);
            }
        }

        if(job.parent)
        {
            // clear folder state
            KMFolderImap *fld = static_cast<KMFolderImap*>(job.parent->storage());
            fld->setCheckingValidity(false);
            fld->quiet(false);
            fld->setContentState(KMFolderImap::imapNoInformation);
            fld->setSubfolderState(KMFolderImap::imapNoInformation);
            fld->sendFolderComplete(FALSE);
            fld->removeJobs();
        }

        if(job.progressItem)
        {
            job.progressItem->setComplete();
        }
    }

    if(mSlave && mapJobData.begin() != mapJobData.end())
    {
        mSlave->kill();
        mSlave = 0;
    }

    // remove the jobs
    mapJobData.clear();

    // KMAccount::deleteFolderJobs(); doesn't work here always, it deletes jobs from
    // its own mJobList instead of our mJobList...
    KMAccount::deleteFolderJobs();

    for(const auto &job : mJobList)
        job->kill();
    mJobList.clear();

    // make sure that no new-mail-check is blocked
    if(mCountRemainChecks > 0)
    {
        checkDone(false, CheckOK);   // returned 0 new messages
        mCountRemainChecks = 0;
    }

    if(disconnectSlave && slave())
    {
        KIO::Scheduler::disconnectSlave(slave());
        mSlave = 0;
    }
}


void KMAcctImap::ignoreJobsForMessage(KMMessage *msg)
{
    if(msg)
    {
        for(const auto &job : mJobList)
        {
            if(job->msgList().first() == msg)
                job->kill();
        }
    }
}


void KMAcctImap::ignoreJobsForFolder(KMFolder *folder)
{
    for(const auto &job : mJobList)
    {
        if(!job->msgList().isEmpty() && job->msgList().first()->parent() == folder)
            job->kill();
    }
}


void KMAcctImap::removeSlaveJobsForFolder(KMFolder *folder)
{
    // Make sure the folder is not referenced in any kio slave jobs
    for(auto it = mapJobData.begin(); it != mapJobData.end();)
    {
        if((*it).parent)
            mapJobData.remove(it++);
        else
            ++it;
    }
}


void KMAcctImap::cancelMailCheck()
{
    // Make list of folders to reset, like in killAllJobs
    QValueList<KMFolderImap*> folderList;

    for(const auto &job : mapJobData)
    {
        if(job.cancellable && job.parent)
            folderList << static_cast<KMFolderImap*>(job.parent->storage());
    }

    // kill jobs
    killAllJobs(true);

    // emit folderComplete, this is important for
    // KMAccount::checkingMail() to be reset, in case we restart checking mail later.
    for(const auto &folder : folderList)
        folder->sendFolderComplete(false);
}


void KMAcctImap::processNewMail(bool interactive)
{
    kdDebug(5006) << "KMAcctImap::processNewMail(interactive: " << interactive << ")" << endl;

    if(!mFolder || !mFolder->folder() || !mFolder->folder()->child() || makeConnection() == ImapAccountBase::Error)
    {
        mCountRemainChecks = 0;
        mCheckingSingleFolder = false;
        checkDone(false, CheckError);

        return;
    }

    // if necessary then initialize the list of folders which should be checked
    if(mMailCheckFolders.isEmpty())
    {
        slotUpdateFolderList();

        // if no folders should be checked then the check is finished
        if(mMailCheckFolders.isEmpty())
        {
            checkDone(false, CheckOK);
            mCheckingSingleFolder = false;

            return;
        }
    }

    // Ok, we're really checking, get a progress item;
    assert(!mMailCheckProgressItem);
    mMailCheckProgressItem =
        ProgressManager::createProgressItem(
            "MailCheckAccount" + name(),
            i18n("Checking account: %1").arg(QStyleSheet::escape(name())),
            QString::null, // status
            true, // can be canceled
            useSSL() || useTLS());

    mMailCheckProgressItem->setTotalItems(mMailCheckFolders.count());
    connect(mMailCheckProgressItem,
            SIGNAL(progressItemCanceled(KPIM::ProgressItem*)),
            this,
            SLOT(slotMailCheckCanceled()));

    QValueList<QGuardedPtr<KMFolder> >::Iterator it;

    // first get the current count of unread-messages
    mCountRemainChecks = 0;
    mCountUnread = 0;
    mUnreadBeforeCheck.clear();

    for(const auto &folder : mMailCheckFolders)
    {
        if(folder && !folder->noContent())
            mUnreadBeforeCheck[folder->idString()] = folder->countUnread();
    }

    bool gotError = false;

    // then check for new mails
    for(const auto &folder : mMailCheckFolders)
    {
        if(folder && !folder->noContent())
        {
            KMFolderImap *imapFolder = static_cast<KMFolderImap*>(folder->storage());

            if(imapFolder->getContentState() != KMFolderImap::imapListingInProgress
                    && imapFolder->getContentState() != KMFolderImap::imapDownloadInProgress)
            {
                // connect the result-signals for new-mail-notification
                mCountRemainChecks++;

                if(imapFolder->isSelected())
                {
                    connect(imapFolder, SIGNAL(folderComplete(KMFolderImap*, bool)), this, SLOT(postProcessNewMail(KMFolderImap*, bool)));
                    imapFolder->getFolder();
                }
                else if(kmkernel->filterMgr()->atLeastOneIncomingFilterAppliesTo(id()) &&
                        imapFolder->folder()->isSystemFolder() &&
                        imapFolder->imapPath() == "/INBOX/")
                {
                    // will be closed in the folderSelected slot
                    imapFolder->open("acctimap");

                    // first get new headers before we select the folder
                    imapFolder->setSelected(true);

                    connect(imapFolder, SIGNAL(folderComplete(KMFolderImap*, bool)), this, SLOT(slotFolderSelected(KMFolderImap*, bool)));
                    imapFolder->getFolder();
                }
                else
                {
                    connect(imapFolder, SIGNAL(numUnreadMsgsChanged(KMFolder*)), this, SLOT(postProcessNewMail(KMFolder*)));

                    bool ok = imapFolder->processNewMail(interactive);
                    if(!ok)
                    {
                        // there was an error so cancel
                        mCountRemainChecks--;
                        gotError = true;
                        if(mMailCheckProgressItem)
                        {
                            mMailCheckProgressItem->incCompletedItems();
                            mMailCheckProgressItem->updateProgress();
                        }
                    }
                }
            }
        }
    } // end for

    if(gotError)
        slotUpdateFolderList();

    // for the case the account is down and all folders report errors
    if(mCountRemainChecks == 0)
    {
        mCountLastUnread = 0; // => mCountUnread - mCountLastUnread == new count
        ImapAccountBase::postProcessNewMail();
        mUnreadBeforeCheck.clear();
        mCheckingSingleFolder = false;
    }
}


void KMAcctImap::postProcessNewMail(KMFolderImap *folder, bool)
{
    disconnect(folder, SIGNAL(folderComplete(KMFolderImap*, bool)), this, SLOT(postProcessNewMail(KMFolderImap*, bool)));
    postProcessNewMail(static_cast<KMFolder*>(folder->folder()));
}


void KMAcctImap::postProcessNewMail(KMFolder *folder)
{
    disconnect(folder->storage(), SIGNAL(numUnreadMsgsChanged(KMFolder*)), this, SLOT(postProcessNewMail(KMFolder*)));

    if(mMailCheckProgressItem)
    {
        mMailCheckProgressItem->incCompletedItems();
        mMailCheckProgressItem->updateProgress();
        mMailCheckProgressItem->setStatus(folder->prettyURL() + i18n(" completed"));
    }
    mCountRemainChecks--;

    // count the unread messages
    const QString folderId = folder->idString();
    int newInFolder = folder->countUnread();

    if(mUnreadBeforeCheck.find(folderId) != mUnreadBeforeCheck.end())
        newInFolder -= mUnreadBeforeCheck[folderId];

    if(newInFolder > 0)
    {
        addToNewInFolder(folderId, newInFolder);
        mCountUnread += newInFolder;
    }

    // Filter messages
    QValueListIterator<Q_UINT32> filterIt = mFilterSerNums.begin();
    QValueList<Q_UINT32> inTransit;

    if(ActionScheduler::isEnabled() || kmkernel->filterMgr()->atLeastOneOnlineImapFolderTarget())
    {
        KMFilterMgr::FilterSet set = KMFilterMgr::Inbound;
        auto filters = kmkernel->filterMgr()->filters();

        if(!mScheduler)
        {
            mScheduler = new KMail::ActionScheduler(set, filters);
            mScheduler->setAccountId(id());
            connect(mScheduler, SIGNAL(filtered(Q_UINT32)), this, SLOT(slotFiltered(Q_UINT32)));
        }
        else
        {
            mScheduler->setFilterList(filters);
        }
    }

    while(filterIt != mFilterSerNums.end())
    {
        int idx = -1;
        KMFolder *folder = 0;
        KMMessage *msg = 0;
        KMMsgDict::instance()->getLocation(*filterIt, &folder, &idx);

        // It's possible that the message has been deleted or moved into a
        // different folder, or that the serNum is stale
        if(!folder)
        {
            mFilterSerNumsToSave.remove(QString::number(*filterIt));
            ++filterIt;
            continue;
        }

        KMFolderImap *imapFolder = dynamic_cast<KMFolderImap*>(folder->storage());

        // sanity checking
        if(!imapFolder || !imapFolder->folder()->isSystemFolder() || !(imapFolder->imapPath() == "/INBOX/"))
        {
            mFilterSerNumsToSave.remove(QString("%1").arg(*filterIt));
            ++filterIt;
            continue;
        }

        if(idx != -1)
        {
            msg = folder->getMsg(idx);

            // sanity checking
            if(!msg)
            {
                mFilterSerNumsToSave.remove(QString("%1").arg(*filterIt));
                ++filterIt;
                continue;
            }

            if(ActionScheduler::isEnabled() || kmkernel->filterMgr()->atLeastOneOnlineImapFolderTarget())
            {
                mScheduler->execFilters(msg);
            }
            else
            {
                if(msg->transferInProgress())
                {
                    inTransit.append(*filterIt);
                    ++filterIt;
                    continue;
                }

                msg->setTransferInProgress(true);
                if(!msg->isComplete())
                {
                    FolderJob *job = folder->createJob(msg);
                    connect(job, SIGNAL(messageRetrieved(KMMessage *)), SLOT(slotFilterMsg(KMMessage *)));
                    job->start();
                }
                else
                {
                    mFilterSerNumsToSave.remove(QString("%1").arg(*filterIt));
                    if(slotFilterMsg(msg) == 2) break;
                }
            }
        }

        ++filterIt;
    }

    mFilterSerNums = inTransit;

    if(mCountRemainChecks == 0)
    {
        // all checks are done
        mCountLastUnread = 0; // => mCountUnread - mCountLastUnread == new count

        // when we check only one folder (=selected) and we have new mails
        // then do not display a summary as the normal status message is better
        bool showStatus = (mCheckingSingleFolder && mCountUnread > 0) ? false : true;
        ImapAccountBase::postProcessNewMail(showStatus);
        mUnreadBeforeCheck.clear();
        mCheckingSingleFolder = false;
    }
}


void KMAcctImap::slotFiltered(Q_UINT32 serNum)
{
    mFilterSerNumsToSave.remove(QString::number(serNum));
}


void KMAcctImap::slotUpdateFolderList()
{
    if(!mFolder || !mFolder->folder() || !mFolder->folder()->child())
        return;

    QStringList strList;
    mMailCheckFolders.clear();
    kmkernel->imapFolderMgr()->createFolderList(&strList, &mMailCheckFolders, mFolder->folder()->child(), QString::null, false);

    // the new list
    QValueList<QGuardedPtr<KMFolder> > includedFolders;

    // check for excluded folders
    for(const auto &mailCheckFolder : mMailCheckFolders)
    {
        KMFolderImap *folder = static_cast<KMFolderImap*>(mailCheckFolder->storage());
        if(folder->includeInMailCheck())
            includedFolders.append(mailCheckFolder);
    }

    mMailCheckFolders = includedFolders;
}


void KMAcctImap::listDirectory()
{
    mFolder->listDirectory();
}


void KMAcctImap::readConfig(KConfig &config)
{
    ImapAccountBase::readConfig(config);
}


void KMAcctImap::slotMailCheckCanceled()
{
    if(mMailCheckProgressItem)
        mMailCheckProgressItem->setComplete();

    cancelMailCheck();
}


FolderStorage *const KMAcctImap::rootFolder() const
{
    return mFolder;
}


ImapAccountBase::ConnectionState KMAcctImap::makeConnection()
{
    ImapAccountBase::ConnectionState state = Error;

    if(mSlaveConnectionError)
        mErrorTimer.start(100, true); // Clear error flag
    else
        state = ImapAccountBase::makeConnection();

    static const char *states[3] = { "Error", "Connected", "Connecting" };
    kdDebug(5006) << "KMAcctImap::makeConnection() => state: " << states[state] << endl;

    return state;
}


void KMAcctImap::slotResetConnectionError()
{
    kdDebug(5006) << "KMAcctImap::slotResetConnectionError()" << endl;
    mSlaveConnectionError = false;
}


void KMAcctImap::slotFolderSelected(KMFolderImap *folder, bool)
{
    folder->setSelected(false);

    disconnect(folder, SIGNAL(folderComplete(KMFolderImap *, bool)), this, SLOT(slotFolderSelected(KMFolderImap *, bool)));
    postProcessNewMail(static_cast<KMFolder*>(folder->folder()));

    folder->close("acctimap");
}


void KMAcctImap::execFilters(Q_UINT32 serNum)
{
    if(!kmkernel->filterMgr()->atLeastOneFilterAppliesTo(id()))
        return;

    if(mFilterSerNums.contains(serNum))
        return;

    mFilterSerNums.append(serNum);
    mFilterSerNumsToSave.insert(QString::number(serNum), 1);
}


int KMAcctImap::slotFilterMsg(KMMessage *msg)
{
    // messageRetrieved(0) is always possible
    if(!msg)
        return -1;

    msg->setTransferInProgress(false);

    ulong serNum = msg->getMsgSerNum();
    if(serNum)
        mFilterSerNumsToSave.remove(QString::number(serNum));

    int filterResult = kmkernel->filterMgr()->process(msg, KMFilterMgr::Inbound, true, id());

    if(filterResult == 2)
    {
        // something went horribly wrong (out of space?)
        kmkernel->emergencyExit(i18n("Unable to process messages: ") + QString::fromLocal8Bit(strerror(errno)));

        return 2;
    }

    if(msg->parent()) // unGet this msg
    {
        int idx;
        KMFolder *p;
        KMMsgDict::instance()->getLocation(msg, &p, &idx);

        assert(p == msg->parent());
        assert(idx >= 0);

        p->unGetMsg(idx);
    }

    return filterResult;
}


#include "kmacctimap.moc"
