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
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
    USA.
*/

#ifndef CONFIGGUIIRMC_H
#define CONFIGGUIIRMC_H

#include <qcheckbox.h>
#include <qdom.h>

#include "configgui.h"
#include "connectionwidgets.h"

class KComboBox;
class KLineEdit;
class QCheckBox;
class QPushButton;
class QSpinBox;

class ConfigGuiIRMC : public ConfigGui {
    Q_OBJECT

public:
    ConfigGuiIRMC(const QSync::Member &, QWidget *parent);

    void load(const QString &xml);
    QString save() const;

protected slots:
    void connectionTypeChanged(int type);

private:
    void initGUI();

    KComboBox *mConnectionType;
    QCheckBox *mDontTellSync;

    BluetoothWidget *mBluetoothWidget;
    IRWidget *mIRWidget;
    CableWidget *mCableWidget;
};

#endif
