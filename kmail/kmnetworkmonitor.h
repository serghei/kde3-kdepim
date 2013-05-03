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
#ifndef _KMNETWORKMONITOR_H_
#define _KMNETWORKMONITOR_H_

#include <qobject.h>

class KMNetworkMonitorPrivate;


class KMNetworkMonitor : public QObject {

    Q_OBJECT

    friend class KMNetworkMonitorPrivate;

public:
    KMNetworkMonitor(QObject *parent = 0, const char *name = 0);
    ~KMNetworkMonitor();

signals:
    void stateChanged(bool);

private:
    KMNetworkMonitorPrivate *d;
};


#endif
