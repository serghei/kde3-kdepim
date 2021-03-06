/*
    This file is part of libkcal.

    Copyright (c) 1998 Preston Brown <pbrown@kde.org>
    Copyright (c) 2001,2003,2004 Cornelius Schumacher <schumacher@kde.org>
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

#include <qdatetime.h>
#include <qstring.h>
#include <qptrlist.h>

#include <kdebug.h>
#include <klocale.h>
#include <kmessagebox.h>

#include "vcaldrag.h"
#include "vcalformat.h"
#include "icalformat.h"
#include "exceptions.h"
#include "incidence.h"
#include "journal.h"
#include "filestorage.h"

#include "calendarlocal.h"

using namespace KCal;

CalendarLocal::CalendarLocal(const QString &timeZoneId)
    : Calendar(timeZoneId), mEvents(47)
{
    init();
}

void CalendarLocal::init()
{
    mDeletedIncidences.setAutoDelete(true);
    mFileName = QString::null;
}


CalendarLocal::~CalendarLocal()
{
    close();
}

bool CalendarLocal::load(const QString &fileName, CalFormat *format)
{
    mFileName = fileName;
    FileStorage storage(this, fileName, format);
    return storage.load();
}

bool CalendarLocal::reload(const QString &tz)
{
    const QString filename = mFileName;
    save();
    close();
    mFileName = filename;
    setTimeZoneId(tz);
    FileStorage storage(this, mFileName);
    return storage.load();
}

bool CalendarLocal::save(const QString &fileName, CalFormat *format)
{
    // Save only if the calendar is either modified, or saved to a
    // different file than it was loaded from
    if(mFileName != fileName || isModified())
    {
        FileStorage storage(this, fileName, format);
        return storage.save();
    }
    else
    {
        return true;
    }
}

void CalendarLocal::close()
{
    setObserversEnabled(false);
    mFileName = QString::null;

    deleteAllEvents();
    deleteAllTodos();
    deleteAllJournals();

    mDeletedIncidences.clear();
    setModified(false);

    setObserversEnabled(true);
}


bool CalendarLocal::addEvent(Event *event)
{
    insertEvent(event);

    event->registerObserver(this);

    setModified(true);

    notifyIncidenceAdded(event);

    return true;
}

bool CalendarLocal::deleteEvent(Event *event)
{
    //  kdDebug(5800) << "CalendarLocal::deleteEvent" << endl;

    if(mEvents.remove(event->uid()))
    {
        setModified(true);
        notifyIncidenceDeleted(event);
        mDeletedIncidences.append(event);
        return true;
    }
    else
    {
        kdWarning() << "CalendarLocal::deleteEvent(): Event not found." << endl;
        return false;
    }
}

void CalendarLocal::deleteAllEvents()
{
    // kdDebug(5800) << "CalendarLocal::deleteAllEvents" << endl;
    QDictIterator<Event> it(mEvents);
    while(it.current())
    {
        notifyIncidenceDeleted(it.current());
        ++it;
    }

    mEvents.setAutoDelete(true);
    mEvents.clear();
    mEvents.setAutoDelete(false);
}

Event *CalendarLocal::event(const QString &uid)
{
    //  kdDebug(5800) << "CalendarLocal::event(): " << uid << endl;
    return mEvents[ uid ];
}

bool CalendarLocal::addTodo(Todo *todo)
{
    mTodoList.append(todo);

    todo->registerObserver(this);

    // Set up subtask relations
    setupRelations(todo);

    setModified(true);

    notifyIncidenceAdded(todo);

    return true;
}

bool CalendarLocal::deleteTodo(Todo *todo)
{
    // Handle orphaned children
    removeRelations(todo);

    if(mTodoList.removeRef(todo))
    {
        setModified(true);
        notifyIncidenceDeleted(todo);
        mDeletedIncidences.append(todo);
        return true;
    }
    else
    {
        kdWarning() << "CalendarLocal::deleteTodo(): Todo not found." << endl;
        return false;
    }
}

void CalendarLocal::deleteAllTodos()
{
    // kdDebug(5800) << "CalendarLocal::deleteAllTodos()\n";
    Todo::List::ConstIterator it;
    for(it = mTodoList.begin(); it != mTodoList.end(); ++it)
    {
        notifyIncidenceDeleted(*it);
    }

    mTodoList.setAutoDelete(true);
    mTodoList.clearAll();
    mTodoList.setAutoDelete(false);
}

Todo::List CalendarLocal::rawTodos(TodoSortField sortField,
                                   SortDirection sortDirection)
{
    return sortTodos(&mTodoList, sortField, sortDirection);
}

Todo *CalendarLocal::todo(const QString &uid)
{
    Todo::List::ConstIterator it;
    for(it = mTodoList.begin(); it != mTodoList.end(); ++it)
    {
        if((*it)->uid() == uid) return *it;
    }

    return 0;
}

Todo::List CalendarLocal::rawTodosForDate(const QDate &date)
{
    Todo::List todos;

    Todo::List::ConstIterator it;
    for(it = mTodoList.begin(); it != mTodoList.end(); ++it)
    {
        Todo *todo = *it;
        if(todo->hasDueDate() && todo->dtDue().date() == date)
        {
            todos.append(todo);
        }
    }

    return todos;
}

Alarm::List CalendarLocal::alarmsTo(const QDateTime &to)
{
    return alarms(QDateTime(QDate(1900, 1, 1)), to);
}

Alarm::List CalendarLocal::alarms(const QDateTime &from, const QDateTime &to)
{
    //  kdDebug(5800) << "CalendarLocal::alarms(" << from.toString() << " - "
    //                << to.toString() << ")" << endl;

    Alarm::List alarms;

    EventDictIterator it(mEvents);
    for(; it.current(); ++it)
    {
        Event *e = *it;
        if(e->doesRecur()) appendRecurringAlarms(alarms, e, from, to);
        else appendAlarms(alarms, e, from, to);
    }

    Todo::List::ConstIterator it2;
    for(it2 = mTodoList.begin(); it2 != mTodoList.end(); ++it2)
    {
        if(!(*it2)->isCompleted()) appendAlarms(alarms, *it2, from, to);
    }

    return alarms;
}

void CalendarLocal::appendAlarms(Alarm::List &alarms, Incidence *incidence,
                                 const QDateTime &from, const QDateTime &to)
{
    QDateTime preTime = from.addSecs(-1);
    Alarm::List::ConstIterator it;
    for(it = incidence->alarms().begin(); it != incidence->alarms().end();
            ++it)
    {
        if((*it)->enabled())
        {
            QDateTime dt = (*it)->nextRepetition(preTime);
            if(dt.isValid() && dt <= to)
            {
                kdDebug(5800) << "CalendarLocal::appendAlarms() '"
                              << incidence->summary() << "': "
                              << dt.toString() << endl;
                alarms.append(*it);
            }
        }
    }
}

void CalendarLocal::appendRecurringAlarms(Alarm::List &alarms,
        Incidence *incidence,
        const QDateTime &from,
        const QDateTime &to)
{
    QDateTime qdt;
    int  endOffset = 0;
    bool endOffsetValid = false;
    int  period = from.secsTo(to);
    Alarm::List::ConstIterator it;
    for(it = incidence->alarms().begin(); it != incidence->alarms().end();
            ++it)
    {
        Alarm *alarm = *it;
        if(alarm->enabled())
        {
            if(alarm->hasTime())
            {
                // The alarm time is defined as an absolute date/time
                qdt = alarm->nextRepetition(from.addSecs(-1));
                if(!qdt.isValid() || qdt > to)
                    continue;
            }
            else
            {
                // The alarm time is defined by an offset from the event start or end time.
                // Find the offset from the event start time, which is also used as the
                // offset from the recurrence time.
                int offset = 0;
                if(alarm->hasStartOffset())
                {
                    offset = alarm->startOffset().asSeconds();
                }
                else if(alarm->hasEndOffset())
                {
                    if(!endOffsetValid)
                    {
                        endOffset = incidence->dtStart().secsTo(incidence->dtEnd());
                        endOffsetValid = true;
                    }
                    offset = alarm->endOffset().asSeconds() + endOffset;
                }

                // Adjust the 'from' date/time and find the next recurrence at or after it
                qdt = incidence->recurrence()->getNextDateTime(from.addSecs(-offset - 1));
                if(!qdt.isValid()
                        || (qdt = qdt.addSecs(offset)) > to)         // remove the adjustment to get the alarm time
                {
                    // The next recurrence is too late.
                    if(!alarm->repeatCount())
                        continue;
                    // The alarm has repetitions, so check whether repetitions of previous
                    // recurrences fall within the time period.
                    bool found = false;
                    qdt = from.addSecs(-offset);
                    while((qdt = incidence->recurrence()->getPreviousDateTime(qdt)).isValid())
                    {
                        int toFrom = qdt.secsTo(from) - offset;
                        if(toFrom > alarm->duration())
                            break;     // this recurrence's last repetition is too early, so give up
                        // The last repetition of this recurrence is at or after 'from' time.
                        // Check if a repetition occurs between 'from' and 'to'.
                        int snooze = alarm->snoozeTime() * 60;   // in seconds
                        if(period >= snooze
                                ||   toFrom % snooze == 0
                                || (toFrom / snooze + 1) * snooze <= toFrom + period)
                        {
                            found = true;
#ifndef NDEBUG
                            qdt = qdt.addSecs(offset + ((toFrom - 1) / snooze + 1) * snooze);   // for debug output
#endif
                            break;
                        }
                    }
                    if(!found)
                        continue;
                }
            }
            kdDebug(5800) << "CalendarLocal::appendAlarms() '" << incidence->summary()
                          << "': " << qdt.toString() << endl;
            alarms.append(alarm);
        }
    }
}


void CalendarLocal::incidenceUpdated(IncidenceBase *incidence)
{
    incidence->setLastModified(QDateTime::currentDateTime());
    // we should probably update the revision number here,
    // or internally in the Event itself when certain things change.
    // need to verify with ical documentation.

    // The static_cast is ok as the CalendarLocal only observes Incidence objects
    notifyIncidenceChanged(static_cast<Incidence *>(incidence));

    setModified(true);
}

void CalendarLocal::insertEvent(Event *event)
{
    QString uid = event->uid();
    if(mEvents[ uid ] == 0)
    {
        mEvents.insert(uid, event);
    }
#ifndef NDEBUG
    else // if we already have an event with this UID, it has to be the same event,
        // otherwise something's really broken
        Q_ASSERT(mEvents[uid] == event);
#endif
}

Event::List CalendarLocal::rawEventsForDate(const QDate &qd,
        EventSortField sortField,
        SortDirection sortDirection)
{
    Event::List eventList;

    EventDictIterator it(mEvents);
    for(; it.current(); ++it)
    {
        Event *event = *it;

        if(event->doesRecur())
        {
            if(event->isMultiDay())
            {
                int extraDays = event->dtStart().date().daysTo(event->dtEnd().date());
                int i;
                for(i = 0; i <= extraDays; i++)
                {
                    if(event->recursOn(qd.addDays(-i)))
                    {
                        eventList.append(event);
                        break;
                    }
                }
            }
            else
            {
                if(event->recursOn(qd))
                    eventList.append(event);
            }
        }
        else
        {
            if(event->dtStart().date() <= qd && event->dateEnd() >= qd)
            {
                eventList.append(event);
            }
        }
    }

    return sortEvents(&eventList, sortField, sortDirection);
}

Event::List CalendarLocal::rawEvents(const QDate &start, const QDate &end,
                                     bool inclusive)
{
    Event::List eventList;
    QDate yesterStart = start.addDays(-1);

    // Get non-recurring events
    EventDictIterator it(mEvents);
    for(; it.current(); ++it)
    {
        Event *event = *it;

        QDate rStart = event->dtStart().date();
        if(end < rStart)
        {
            //      kdDebug(5800) << "Skipping event starting after TOI" << endl;
            continue;
        }
        if(inclusive && rStart < start)
        {
            //      kdDebug(5800) << "Skipping event starting before TOI while inclusive" << endl;
            continue;
        }

        if(! event->doesRecur())      // non-recurring events
        {
            QDate rEnd = event->dtEnd().date();
            if(rEnd < start)
            {
                //        kdDebug(5800) << "Skipping event ending before TOI" << endl;
                continue;
            }
            if(inclusive && end < rEnd)
            {
                //        kdDebug(5800) << "Skipping event ending after TOI while inclusive" << endl;
                continue;
            }
        }
        else     // recurring events
        {
            switch(event->recurrence()->duration())
            {
                case -1: // infinite
                    if(inclusive)
                    {
                        //            kdDebug(5800) << "Skipping infinite event because inclusive" << endl;
                        continue;
                    }
                    break;
                case 0: // end date given
                default: // count given
                    QDate rEnd = event->recurrence()->endDate();
                    if(! rEnd.isValid())
                    {
                        //            kdDebug(5800) << "Skipping recurring event without occurences" << endl;
                        continue;
                    }
                    if(rEnd < start)
                    {
                        //            kdDebug(5800) << "Skipping recurring event ending before TOI" << endl;
                        continue;
                    }
                    if(inclusive && end < rEnd)
                    {
                        //            kdDebug(5800) << "Skipping recurring event ending after TOI while inclusive" << endl;
                        continue;
                    }
                    /* FIXME: too much conversion between QDate and QDateTime makes this useless:
                     *   freebusy(end=QDateTime(day, "00:00:00")) ->
                     *   rawEvents(end=QDate(day)) ->
                     *   durationTo(QDateTime(day, "23:59:59"))
                     * so events repeating at the end day match and are included.
                     */
#if 0
                    int durationBeforeStart = event->recurrence()->durationTo(yesterStart);
                    int durationUntilEnd = event->recurrence()->durationTo(end);
                    if(durationBeforeStart == durationUntilEnd)
                    {
                        kdDebug(5800) << "Skipping recurring event without occurences in TOI" << endl;
                        continue;
                    }
#endif
                    break;
            } // switch(duration)
        } // if(doesRecur)

        eventList.append(event);
    }

    return eventList;
}

Event::List CalendarLocal::rawEventsForDate(const QDateTime &qdt)
{
    return rawEventsForDate(qdt.date());
}

Event::List CalendarLocal::rawEvents(EventSortField sortField, SortDirection sortDirection)
{
    Event::List eventList;
    EventDictIterator it(mEvents);
    for(; it.current(); ++it)
        eventList.append(*it);
    return sortEvents(&eventList, sortField, sortDirection);
}

bool CalendarLocal::addJournal(Journal *journal)
{
    //   if (journal->dtStart().isValid())
    //     kdDebug(5800) << "Adding Journal on " << journal->dtStart().toString() << endl;
    //   else
    //     kdDebug(5800) << "Adding Journal without a DTSTART" << endl;

    mJournalList.append(journal);

    journal->registerObserver(this);

    setModified(true);

    notifyIncidenceAdded(journal);

    return true;
}

bool CalendarLocal::deleteJournal(Journal *journal)
{
    if(mJournalList.removeRef(journal))
    {
        setModified(true);
        notifyIncidenceDeleted(journal);
        mDeletedIncidences.append(journal);
        return true;
    }
    else
    {
        kdWarning() << "CalendarLocal::deleteJournal(): Journal not found." << endl;
        return false;
    }
}

void CalendarLocal::deleteAllJournals()
{
    Journal::List::ConstIterator it;
    for(it = mJournalList.begin(); it != mJournalList.end(); ++it)
    {
        notifyIncidenceDeleted(*it);
    }

    mJournalList.setAutoDelete(true);
    mJournalList.clearAll();
    mJournalList.setAutoDelete(false);
}

Journal *CalendarLocal::journal(const QString &uid)
{
    Journal::List::ConstIterator it;
    for(it = mJournalList.begin(); it != mJournalList.end(); ++it)
        if((*it)->uid() == uid)
            return *it;

    return 0;
}

Journal::List CalendarLocal::rawJournals(JournalSortField sortField, SortDirection sortDirection)
{
    return sortJournals(&mJournalList, sortField, sortDirection);
}

Journal::List CalendarLocal::rawJournalsForDate(const QDate &date)
{
    Journal::List journals;

    Journal::List::ConstIterator it;
    for(it = mJournalList.begin(); it != mJournalList.end(); ++it)
    {
        Journal *journal = *it;
        if(journal->dtStart().date() == date)
        {
            journals.append(journal);
        }
    }

    return journals;
}

void CalendarLocal::setTimeZoneIdViewOnly(const QString &tz)
{
    const QString question(i18n("The timezone setting was changed. In order to display the calendar "
                                "you are looking at in the new timezone, it needs to be saved. Do you want to save the pending "
                                "changes or rather wait and apply the new timezone on the next reload?"));
    int rc = KMessageBox::Yes;
    if(isModified())
    {
        rc = KMessageBox::questionYesNo(0, question,
                                        i18n("Save before applying timezones?"),
                                        KStdGuiItem::save(),
                                        KGuiItem(i18n("Apply Timezone Change on Next Reload")),
                                        "calendarLocalSaveBeforeTimezoneShift");
    }
    if(rc == KMessageBox::Yes)
    {
        reload(tz);
    }
}
