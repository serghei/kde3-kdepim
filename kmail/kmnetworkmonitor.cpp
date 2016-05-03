/*
   This file is part of the KDE3 Fork Project
   Copyright (c) 2013 Serghei Amelian <serghei.amelian@gmail.com>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include <qtimer.h>

#include <dbus/qdbusconnection.h>
#include <dbus/qdbuserror.h>
#include <dbus/qdbusmessage.h>
#include <dbus/qdbusproxy.h>

#include <kdebug.h>

#include "kmnetworkmonitor.h"


class KMNetworkMonitorPrivate : public QDBusProxy {

    Q_OBJECT

public:
    KMNetworkMonitorPrivate(KMNetworkMonitor *parent)
        : QDBusProxy(parent, "KMNetworkMonitorPrivate"), lastStatus(-1)
    {
        setService("org.freedesktop.NetworkManager");
        setPath("/org/freedesktop/NetworkManager");
        setInterface("org.freedesktop.NetworkManager");

        QTimer::singleShot(0, this, SLOT(initialize()));
    }

protected slots:
    void initialize()
    {
        // connect to DBUS
        QDBusConnection dbus = QDBusConnection::systemBus();
        if(!dbus.isConnected())
        {
            kdDebug() << "Unable to connect to DBus: " << dbus.lastError().message() << endl;
            return;
        }
        setConnection(dbus);

        // check for current status
        int rc = sendWithAsyncReply("state", QValueList<QDBusData>());
        if(0 == rc)
        {
            kdDebug() << "Unable to send \"state\" command to DBus" << endl;
            return;
        }
    }

    void handleDBusSignal(const QDBusMessage &message)
    {
        // the message is for us
        if(path() == message.path() && interface() == message.interface() && "StateChanged" == message.member())
            handleMessage(message);
    }

    void handleAsyncReply(const QDBusMessage &message)
    {
        handleMessage(message);
    }

    void handleMessage(const QDBusMessage &message)
    {
        bool ok;
        Q_UINT32 state = message[0].toUInt32(&ok);

        if(!ok)
        {
            kdDebug() << "KMNetworkMonitor: received unexpected type for state (" << message[0].typeName() << ")" << endl;
            return;
        }

        int currStatus = (50 < state ? 1 : 0);

        if(lastStatus != currStatus)
        {
            emit static_cast<KMNetworkMonitor *>(parent())->stateChanged(1 == currStatus);
            lastStatus = currStatus;
        }
    }

private:
    // -1 = unitialized, 0 = offline, 1 = online
    int lastStatus;
};


KMNetworkMonitor::KMNetworkMonitor(QObject *parent, const char *name)
    : QObject(parent, name)
{
    d = new KMNetworkMonitorPrivate(this);
}


KMNetworkMonitor::~KMNetworkMonitor()
{
    delete d;
}


#include "kmnetworkmonitor.moc"
#include "kmnetworkmonitor.cpp.moc"
