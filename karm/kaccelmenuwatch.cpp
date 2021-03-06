/*
* kaccelmenuwatch.cpp -- Implementation of class KAccelMenuWatch.
* Author:    Sirtaj Singh Kang
* Generated: Thu Jan  7 15:05:26 EST 1999
*/

#include <assert.h>
#include <qpopupmenu.h>

#include "kaccelmenuwatch.h"

KAccelMenuWatch::KAccelMenuWatch(KAccel *accel, QObject *parent)
    : QObject(parent),
      _accel(accel),
      _menu(0)
{
    _accList.setAutoDelete(true);
    _menuList.setAutoDelete(false);
}

void KAccelMenuWatch::setMenu(QPopupMenu *menu)
{
    assert(menu);

    // we use  _menuList to ensure that the signal is
    // connected only once per menu.

    if(!_menuList.findRef(menu))
    {
        _menuList.append(menu);
        connect(menu, SIGNAL(destroyed()), this, SLOT(removeDeadMenu()));
    }

    _menu = menu;
}

void KAccelMenuWatch::connectAccel(int itemId, const char *action)
{
    AccelItem *item = newAccelItem(_menu, itemId, StringAccel) ;
    item->action  = QString::fromLocal8Bit(action);
}

void KAccelMenuWatch::connectAccel(int itemId, KStdAccel::StdAccel accel)
{
    AccelItem *item = newAccelItem(_menu, itemId, StdAccel) ;
    item->stdAction  = accel;
}

void KAccelMenuWatch::updateMenus()
{
    assert(_accel != 0);

    QPtrListIterator<AccelItem> iter(_accList);
    AccelItem *item;

    for(; (item = iter.current()) ; ++iter)
    {
        // These setAccel calls were converted from all changeMenuAccel calls
        // as descibed in KDE3PORTING.html
        switch(item->type)
        {
            case StringAccel:
                item->menu->setAccel(_accel->shortcut(item->action).keyCodeQt(), item->itemId);
                break;
            case StdAccel:
                item->menu->setAccel(KStdAccel::shortcut(item->stdAction).keyCodeQt(), item->itemId);
                break;
            default:
                break;
        }
    }

}

void KAccelMenuWatch::removeDeadMenu()
{
    QPopupMenu *sdr = (QPopupMenu *) sender();
    assert(sdr);

    if(!_menuList.findRef(sdr))
        return;

    // remove all accels

    AccelItem *accel;
    for(accel = _accList.first(); accel; accel = _accList.next())
    {
loop:
        if(accel && accel->menu == sdr)
        {
            _accList.remove();
            accel = _accList.current();
            goto loop;
        }
    }

    // remove from menu list
    _menuList.remove(sdr);

    return;
}

KAccelMenuWatch::AccelItem *KAccelMenuWatch::newAccelItem(QPopupMenu *,
        int itemId, AccelType type)
{
    AccelItem *item = new AccelItem;

    item->menu  = _menu;
    item->itemId  = itemId;
    item->type  = type;

    _accList.append(item);

    return item;
}

#include "kaccelmenuwatch.moc"
