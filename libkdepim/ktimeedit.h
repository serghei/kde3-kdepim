/*
    This file is part of libkdepim.

    Copyright (c) 1999 Preston Brown <pbrown@kde.org>
    Copyright (c) 1999 Ian Dawes <iadawes@globalserve.net>

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

    As a special exception, permission is given to link this program
    with any edition of Qt, and distribute the resulting executable,
    without including the source code for Qt in the source distribution.
*/
#ifndef _KTIMEEDIT_H
#define _KTIMEEDIT_H

#include <qevent.h>
#include <qkeycode.h>
#include <qstring.h>
#include <qdatetime.h>
#include <qcombobox.h>

#include <kapplication.h>
#include <kdepimmacros.h>

/**
  This is a class that provides an easy, user friendly way to edit times.
  up/down/ increase or decrease time, respectively.

  @short Provides a way to edit times in a user-friendly manner.
  @author Preston Brown, Ian Dawes
*/
class KDE_EXPORT KTimeEdit : public QComboBox {
    Q_OBJECT
public:
    /** constructs a new time edit. */
    KTimeEdit(QWidget *parent = 0, QTime qt = QTime(12, 0), const char *name = 0);

    virtual ~KTimeEdit();

    /**
      Returns, if a time is selected. Can not return false anymore....
    */
    bool hasTime() const;

    /** returns the time that is currently set in the timeLineEdit. */
    QTime getTime() const;

    /** returns the preferred size policy of the KTimeEdit */
    QSizePolicy sizePolicy() const;

    /** return true if input is a valid time and false if not */
    bool inputIsValid() const;

signals:
    /**
      Emitted every time the time displayed changes. "newt" is the new
      time.
    */
    void timeChanged(QTime newt);

public slots:
    /** used to set the time which is displayed to a specific value. */
    void setTime(QTime qt);

protected slots:
    void active(int);
    void hilit(int);
    void changedText();

protected:
    virtual void keyPressEvent(QKeyEvent *qke);
    void addTime(QTime qt);
    void subTime(QTime qt);
    // Update the lineedit text from mTime
    void updateText();

private:
    QTime mTime;                   // the widget's displayed time.
    //QString mNoTimeString;
};

#endif
