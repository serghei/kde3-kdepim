/************************************************************************\
 *
 *  kmail: KDE mail client
 *
 *  class KMail::AccountManager
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

#include <qregexp.h>

#include <klocale.h>
#include <kmessagebox.h>

#include "broadcaststatus.h"
#include "kmacctcachedimap.h"
#include "kmacctimap.h"
#include "kmacctlocal.h"
#include "kmacctmaildir.h"
#include "kmfiltermgr.h"
#include "popaccount.h"

#include "accountmanager.h"

using namespace KMail;


AccountManager::AccountManager()
    : QObject(nullptr, "KMail::AccountManager")
    , mNewMailArrived(false)
    , mInteractive(false)
    , mTotalNewMailsArrived(0)
    , mDisplaySummary(false)
{
    mAccountChecking.clear();
    mAccountTodo.clear();
}


AccountManager::~AccountManager()
{
    writeConfig(false);
}


void AccountManager::writeConfig(bool withSync)
{
    KConfig *config = KMKernel::config();

    KConfigGroupSaver saver(config, "General");
    config->writeEntry("accounts", mAccountList.count());

    // first delete all account groups in the config file:
    QStringList accountGroups = config->groupList().grep(QRegExp("Account \\d+"));
    for(const auto &group : accountGroups)
        config->deleteGroup(group);

    // now write new account groups:
    int i = 1;
    for(const auto &account : mAccountList)
    {
        QString groupName(QString("Account %1").arg(i++));
        KConfigGroupSaver saver(config, groupName);
        account->writeConfig(*config);
    }

    if(withSync)
        config->sync();
}


void AccountManager::readConfig()
{
    for(auto account : mAccountList)
        delete account;
    mAccountList.clear();

    KConfig *config = KMKernel::config();
    KConfigGroup general(config, "General");
    int numEntry = general.readNumEntry("accounts");

    for(int i = 1; i <= numEntry; i++)
    {
        QString groupName(QString("Account %1").arg(i));
        KConfigGroupSaver saver(config, groupName);
        QString accountType = config->readEntry("Type");
        QString accountName = config->readEntry("Name");
        uint id = config->readUnsignedNumEntry("Id");

        if(accountName.isEmpty())
            accountName = i18n("Account %1").arg(i);

        KMAccount *account = create(accountType, accountName, id);
        if(!account)
            continue;

        add(account);
        account->readConfig(*config);
    }
}


void AccountManager::singleCheckMail(KMAccount *account, bool interactive)
{
    kdDebug(5006) << "AccountManager::singleCheckMail(account: \"" << account->name()
                  << "\", interactive: " << interactive << ")" << endl;

    mNewMailArrived = false;
    mInteractive = interactive;

    // if sync has been requested by the user then check if check-interval was disabled by user, if yes, then
    // de-install the timer
    // Safe guard against an infinite sync loop (kolab/issue2607)
    if(mInteractive)
        account->readTimerConfig();

    // queue the account
    mAccountTodo.append(account);

    if(account->checkingMail())
    {
        kdDebug(5006) << "    account " << account->name() << " busy, queuing" << endl;
        return;
    }

    processNextCheck(false);
}


void AccountManager::processNextCheck(bool newMail)
{
    kdDebug(5006) << "AccountManager::processNextCheck(_newMail: " << newMail << ")" << endl
                  << "    mAccountTodo.count(): " << mAccountTodo.count() << endl;

    if(newMail)
        mNewMailArrived = true;

    for(auto it = mAccountChecking.begin(); it != mAccountChecking.end();)
    {
        KMAccount *account = *it;
        ++it;

        if(account->checkingMail())
            continue;

        // check done
        kdDebug(5006) << "    account " << account->name() << " finished check" << endl;
        mAccountChecking.remove(account);
        kmkernel->filterMgr()->deref();

        disconnect(account, SIGNAL(finishedCheck(bool, CheckStatus)), this, SLOT(processNextCheck(bool)));
    }

    if(mAccountChecking.isEmpty())
    {
        // all checks finished, display summary
        if(mDisplaySummary)
            KPIM::BroadcastStatus::instance()->setStatusMsgTransmissionCompleted(mTotalNewMailsArrived);

        emit checkedMail(mNewMailArrived, mInteractive, mTotalNewInFolder);
        mTotalNewMailsArrived = 0;
        mTotalNewInFolder.clear();
        mDisplaySummary = false;
    }

    if(mAccountTodo.isEmpty())
        return;

    KMAccount *curAccount = nullptr;
    for(auto it = mAccountTodo.begin(); it != mAccountTodo.end(); it++)
    {
        KMAccount *account = *it;

        if(!account->checkingMail() && account->mailCheckCanProceed())
        {
            curAccount = account;
            mAccountTodo.erase(it);
            break;
        }
    }

    // no account or all of them are already checking
    if(!curAccount)
        return;

    if(curAccount->type() != "imap"
       && curAccount->type() != "cachedimap"
       && curAccount->folder() == nullptr)
    {
        KMessageBox::information(0,
                                 i18n("Account %1 has no mailbox defined:\n"
                                      "mail checking aborted;\n"
                                      "check your account settings.")
                                 .arg(curAccount->name()));

        emit checkedMail(false, mInteractive, mTotalNewInFolder);
        mTotalNewMailsArrived = 0;
        mTotalNewInFolder.clear();

        return;
    }

    connect(curAccount, SIGNAL(finishedCheck(bool, CheckStatus)), this, SLOT(processNextCheck(bool)));

    KPIM::BroadcastStatus::instance()->setStatusMsg(
        i18n("Checking account %1 for new mail").arg(curAccount->name()));

    kdDebug(5006) << "    processing next mail check for " << curAccount->name() << endl;

    curAccount->setCheckingMail(true);
    mAccountChecking.append(curAccount);
    kmkernel->filterMgr()->ref();
    curAccount->processNewMail(mInteractive);
}


KMAccount *AccountManager::create(const QString &type, const QString &name, uint id)
{
    KMAccount *account = nullptr;

    if(id == 0)
        id = createId();

    if(type == "local")
    {
        account = new KMAcctLocal(this, name.isEmpty() ? i18n("Local Account") : name, id);
        account->setFolder(kmkernel->inboxFolder());
    }
    else if(type == "maildir")
    {
        account = new KMAcctMaildir(this, name.isEmpty() ? i18n("Local Account") : name, id);
        account->setFolder(kmkernel->inboxFolder());
    }
    else if(type == "pop")
    {
        account = new KMail::PopAccount(this, name.isEmpty() ? i18n("POP Account") : name, id);
        account->setFolder(kmkernel->inboxFolder());
    }
    else if(type == "imap")
    {
        account = new KMAcctImap(this, name.isEmpty() ? i18n("IMAP Account") : name, id);
    }
    else if(type == "cachedimap")
    {
        account = new KMAcctCachedImap(this, name.isEmpty() ? i18n("IMAP Account") : name, id);
    }

    if(!account)
    {
        kdWarning(5006) << "Attempt to instantiate a non-existing account type!" << endl;
        return nullptr;
    }

    connect(account, SIGNAL(newMailsProcessed(const QMap<QString, int> &)),
            this, SLOT(addToTotalNewMailCount(const QMap<QString, int> &)));

    return account;
}


void AccountManager::add(KMAccount *account)
{
    if(account)
    {
        mAccountList.append(account);
        emit accountAdded(account);
        account->installTimer();
    }
}


KMAccount *AccountManager::findByName(const QString &name) const
{
    if(!name.isEmpty())
    {
        for(const auto &account : mAccountList)
        {
            if(account->name() == name)
                return account;
        }
    }

    return nullptr;
}


KMAccount *AccountManager::find(const uint id) const
{
    if(id)
    {
        for(const auto &account : mAccountList)
        {
            if(account->id() == id)
                return account;
        }
    }

    return nullptr;
}


KMAccount *AccountManager::first()
{
    if(mAccountList.empty())
        return nullptr;

    return *(mPtrListInterfaceProxyIterator = mAccountList.begin());
}


KMAccount *AccountManager::next()
{
    if(mAccountList.empty() || (++mPtrListInterfaceProxyIterator) == mAccountList.end())
        return nullptr;

    return *mPtrListInterfaceProxyIterator;
}


bool AccountManager::remove(KMAccount *account)
{
    if(!account)
        return false;

    mAccountList.remove(account);
    emit accountRemoved(account);

    return true;
}


void AccountManager::checkMail(bool interactive)
{
    kdDebug(5006) << "AccountManager::checkMail(interactive: " << interactive << ")" << endl;

    mNewMailArrived = false;

    if(mAccountList.isEmpty())
    {
        KMessageBox::information(0, i18n("You need to add an account in the network "
                                         "section of the settings in order to receive mail."));
        return;
    }

    mDisplaySummary = true;
    mTotalNewMailsArrived = 0;
    mTotalNewInFolder.clear();

    for(const auto &account : mAccountList)
    {
        if(!account->checkExclude())
            singleCheckMail(account, interactive);
    }
}


void AccountManager::singleInvalidateIMAPFolders(KMAccount *account)
{
    account->invalidateIMAPFolders();
}


void AccountManager::invalidateIMAPFolders()
{
    for(const auto &account : mAccountList)
        singleInvalidateIMAPFolders(account);
}


QStringList AccountManager::getAccounts() const
{
    QStringList strList;

    for(const auto &account : mAccountList)
        strList.append(account->name());

    return strList;
}


void AccountManager::intCheckMail(int item, bool _interactive)
{
    mNewMailArrived = false;
    mTotalNewMailsArrived = 0;
    mTotalNewInFolder.clear();

    if(KMAccount *account = mAccountList[item])
        singleCheckMail(account, _interactive);

    mDisplaySummary = false;
}


void AccountManager::addToTotalNewMailCount(const QMap<QString, int> &newInFolder)
{
    for(auto it = newInFolder.begin(); it != newInFolder.end(); ++it)
    {
        mTotalNewMailsArrived += it.data();

        if(mTotalNewInFolder.contains(it.key()))
           mTotalNewInFolder[it.key()] += it.data();
        else
           mTotalNewInFolder[it.key()] = it.data();

    }
}


uint AccountManager::createId()
{
    QValueList<uint> usedIds;
    usedIds << 0; // 0 is default for unknown

    for(const auto &account : mAccountList)
        usedIds << account->id();

    // create a new random id
    uint newId = static_cast<uint>(kapp->random());

    // ensure that the id is unique
    while(usedIds.contains(newId))
        newId = static_cast<uint>(kapp->random());

    return newId;
}


void AccountManager::cancelMailCheck()
{
    for(const auto &account : mAccountList)
        account->cancelMailCheck();
}


void AccountManager::readPasswords()
{
    for(const auto &account : mAccountList)
    {
        NetworkAccount *networkAccount = dynamic_cast<NetworkAccount*>(account);
        if(networkAccount)
            networkAccount->readPassword();
    }
}


#include "accountmanager.moc"
