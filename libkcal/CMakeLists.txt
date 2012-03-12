#################################################
#
#  (C) 2010-2012 Serghei Amelian
#  serghei (DOT) amelian (AT) gmail.com
#
#  Improvements and feedback are welcome
#
#  This file is released under GPL >= 2
#
#################################################

project( libkcal )

include( ConfigureChecks.cmake )

kde_import( libkmime )
kde_import( ktnef )

add_subdirectory( versit )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/versit
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${CMAKE_SOURCE_DIR}/ktnef
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
  ${LIBICAL_INCLUDE_DIRS}
)


##### headers ###################################

install( FILES
    alarm.h attachment.h attendee.h calendar.h calendarlocal.h
    calendarnull.h calendarresources.h calfilter.h calformat.h
    calstorage.h customproperties.h dndfactory.h duration.h event.h
    exceptions.h filestorage.h freebusy.h htmlexport.h icaldrag.h
    icalformat.h incidencebase.h incidence.h incidenceformatter.h
    journal.h kcalversion.h listbase.h
    period.h person.h qtopiaformat.h recurrencerule.h recurrence.h
    resourcecached.h resourcecalendar.h resourcelocalconfig.h
    resourcelocaldirconfig.h resourcelocaldir.h resourcelocal.h
    scheduler.h libkcal_export.h todo.h vcaldrag.h vcalformat.h
    ${CMAKE_CURRENT_BINARY_DIR}/htmlexportsettings.h
  DESTINATION ${INCLUDE_INSTALL_DIR}/libkcal )


##### other data ################################

install( FILES local.desktop localdir.desktop DESTINATION ${SERVICES_INSTALL_DIR}/kresources/kcal )
install( FILES kcal_manager.desktop DESTINATION ${SERVICES_INSTALL_DIR}/kresources )


##### kcal_local (module) #######################

kde_add_kpart( kcal_local AUTOMOC
  SOURCES resourcelocal_plugin.cpp
  LINK kcal-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### kcal_localdir (module) ####################

kde_add_kpart( kcal_localdir AUTOMOC
  SOURCES resourcelocaldir_plugin.cpp
  LINK kcal-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### kcal (shared) #############################

kde_add_library( kcal SHARED AUTOMOC
  SOURCES
    incidencebase.cpp incidence.cpp journal.cpp todo.cpp event.cpp
    freebusy.cpp attendee.cpp attachment.cpp recurrencerule.cpp
    recurrence.cpp alarm.cpp customproperties.cpp calendar.cpp
    calendarlocal.cpp calformat.cpp vcalformat.cpp icalformat.cpp
    icalformatimpl.cpp incidenceformatter.cpp vcaldrag.cpp
    icaldrag.cpp exceptions.cpp scheduler.cpp imipscheduler.cpp
    dummyscheduler.cpp calfilter.cpp person.cpp period.cpp
    duration.cpp dndfactory.cpp filestorage.cpp compat.cpp
    resourcecalendar.cpp resourcelocal.cpp resourcelocalconfig.cpp
    resourcelocaldir.cpp resourcelocaldirconfig.cpp resourcecached.cpp
    resourcecachedconfig.cpp calendarresources.cpp qtopiaformat.cpp
    htmlexportsettings.kcfgc htmlexport.cpp calendarnull.cpp
    freebusyurlstore.cpp confirmsavedialog.cpp
  VERSION 2.0.0
  LINK versit-static emailfunctions-static ktnef-shared kmime-shared kabc-shared ${LIBICAL_LIBRARIES}
  DESTINATION ${LIB_INSTALL_DIR}
)


##### install import cmake modules ###############

kde_install_export( )
