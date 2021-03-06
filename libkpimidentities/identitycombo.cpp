/*  -*- c++ -*-
    identitycombo.cpp

    This file is part of KMail, the KDE mail client.
    Copyright (c) 2002 Marc Mutz <mutz@kde.org>

    KMail is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License, version 2, as
    published by the Free Software Foundation.

    KMail is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

    In addition, as a special exception, the copyright holders give
    permission to link the code of this program with any edition of
    the Qt library by Trolltech AS, Norway (or with modified versions
    of Qt that use the same license as Qt), and distribute linked
    combinations including the two.  You must obey the GNU General
    Public License in all respects for all of the code used other than
    Qt.  If you modify this file, you may extend this exception to
    your version of the file, but you are not obligated to do so.  If
    you do not wish to do so, delete this exception statement from
    your version.
*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "identitycombo.h"
#include "identity.h"
#include "identitymanager.h"

#include <klocale.h>

#include <assert.h>

using namespace KPIM;

IdentityCombo::IdentityCombo(IdentityManager *manager, QWidget *parent, const char *name)
    : QComboBox(false, parent, name), mIdentityManager(manager)
{
    reloadCombo();
    reloadUoidList();
    connect(this, SIGNAL(activated(int)), SLOT(slotEmitChanged(int)));
    connect(manager, SIGNAL(changed()),
            SLOT(slotIdentityManagerChanged()));
}

QString IdentityCombo::currentIdentityName() const
{
    return mIdentityManager->identities()[ currentItem() ];
}

uint IdentityCombo::currentIdentity() const
{
    return mUoidList[ currentItem() ];
}

void IdentityCombo::setCurrentIdentity(const Identity &identity)
{
    setCurrentIdentity(identity.uoid());
}

void IdentityCombo::setCurrentIdentity(const QString &name)
{
    int idx = mIdentityManager->identities().findIndex(name);
    if(idx < 0) return;
    if(idx == currentItem()) return;

    blockSignals(true);   // just in case Qt gets fixed to emit activated() here
    setCurrentItem(idx);
    blockSignals(false);

    slotEmitChanged(idx);
}

void IdentityCombo::setCurrentIdentity(uint uoid)
{
    int idx = mUoidList.findIndex(uoid);
    if(idx < 0) return;
    if(idx == currentItem()) return;

    blockSignals(true);   // just in case Qt gets fixed to emit activated() here
    setCurrentItem(idx);
    blockSignals(false);

    slotEmitChanged(idx);
}

void IdentityCombo::reloadCombo()
{
    QStringList identities = mIdentityManager->identities();
    // the IM should prevent this from happening:
    assert(!identities.isEmpty());
    identities.first() = i18n("%1 (Default)").arg(identities.first());
    clear();
    insertStringList(identities);
}

void IdentityCombo::reloadUoidList()
{
    mUoidList.clear();
    IdentityManager::ConstIterator it;
    for(it = mIdentityManager->begin() ; it != mIdentityManager->end() ; ++it)
        mUoidList << (*it).uoid();
}

void IdentityCombo::slotIdentityManagerChanged()
{
    uint oldIdentity = mUoidList[ currentItem() ];

    reloadUoidList();
    int idx = mUoidList.findIndex(oldIdentity);

    blockSignals(true);
    reloadCombo();
    setCurrentItem(idx < 0 ? 0 : idx);
    blockSignals(false);

    if(idx < 0)
        // apparently our oldIdentity got deleted:
        slotEmitChanged(currentItem());
}

void IdentityCombo::slotEmitChanged(int idx)
{
    emit identityChanged(mIdentityManager->identities()[idx]);
    emit identityChanged(mUoidList[idx]);
}

#include "identitycombo.moc"
