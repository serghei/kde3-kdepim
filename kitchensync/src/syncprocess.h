/*
    This file is part of KitchenSync.

    Copyright (c) 2005 Tobias Koenig <tokoe@kde.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

#ifndef SYNCPROCESS_H
#define SYNCPROCESS_H

#include <qobject.h>

#include <libqopensync/group.h>

namespace QSync {
class Engine;
}

class SyncProcess : public QObject {
    Q_OBJECT

public:
    SyncProcess(const QSync::Group &group);
    ~SyncProcess();

    QSync::Group group() const
    {
        return mGroup;
    }
    QSync::Engine *engine() const
    {
        return mEngine;
    }

    QString groupStatus() const;
    QString memberStatus(const QSync::Member &member) const;

    QSync::Result addMember(const QSync::Plugin &plugin);

    void reinitEngine();

    /** apply object type filter hack **/
    void applyObjectTypeFilter();

signals:
    /**
      This signal is emitted whenever the engine has changed ( reinitialized ).
     */
    void engineChanged(QSync::Engine *engine);

private:
    QSync::Group mGroup;
    QSync::Engine *mEngine;
};

#endif
