/*
    This file is part of libkdepim.

    Copyright (c) 2000, 2001, 2002 Cornelius Schumacher <schumacher@kde.org>
    Copyright (C) 2003-2004 Reinhold Kainhofer <reinhold@kainhofer.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/
#ifndef KPIM_CATEGORYEDITDIALOG_H
#define KPIM_CATEGORYEDITDIALOG_H

#include <kdialogbase.h>
#include <kdepimmacros.h>

class KPimPrefs;

namespace KPIM {

class KDE_EXPORT CategoryEditDialog : public KDialogBase {
    Q_OBJECT
public:
    CategoryEditDialog(KPimPrefs *prefs, QWidget *parent = 0,
                       const char *name = 0,
                       bool modal = false);
    ~CategoryEditDialog();

public slots:
    void reload();

protected slots:
    void slotOk();
    void slotApply();
    void slotCancel();
    void add();
    void edit();
    void remove();

signals:
    void categoryConfigChanged();

protected:
    void fillList();

private:
    KPimPrefs *mPrefs;
    class Private;
    Private *const d;
};

}

#endif
