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

project( korganizer )

include( ConfigureChecks.cmake )
configure_file( ical2vcal.cmake ical2vcal @ONLY )

kde_import( libkdepim )
kde_import( libkmime )
kde_import( ktnef )
kde_import( libkcal )
kde_import( libkdenetwork )
kde_import( certmanager )
kde_import( libkpimidentities )
kde_import( libkholidays )

add_subdirectory( printing )
add_subdirectory( korgac )
add_subdirectory( pixmaps )
add_subdirectory( sounds )
add_subdirectory( plugins )
add_subdirectory( interfaces )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/interfaces
  ${CMAKE_CURRENT_SOURCE_DIR}/printing
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkholidays
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${CMAKE_SOURCE_DIR}/certmanager/lib
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)

link_directories(
  ${QT_LIBRARY_DIR}
)


##### other data ################################

kde_install_icons( )

install( FILES
    korganizer.desktop
  DESTINATION ${XDG_APPS_INSTALL_DIR} )

install( FILES
    dcopcalendar.desktop
  DESTINATION ${SERVICETYPES_INSTALL_DIR} )

install( FILES
    korganizer_configmain.desktop korganizer_configtime.desktop
    korganizer_configviews.desktop korganizer_configcolors.desktop
    korganizer_configfonts.desktop korganizer_configplugins.desktop
    korganizer_configgroupscheduling.desktop korganizer_configfreebusy.desktop
    korganizer_configdesignerfields.desktop webcal.protocol
  DESTINATION ${SERVICES_INSTALL_DIR} )

install( FILES
    uninstall.desktop
  RENAME korganizer_configgroupautomation.desktop
  DESTINATION ${SERVICES_INSTALL_DIR} )

install( FILES
    uninstall.desktop
  RENAME webexport.desktop
  DESTINATION ${SERVICES_INSTALL_DIR}/korganizer )

install( FILES
    uninstall.desktop
  RENAME holidays.desktop
  DESTINATION ${SERVICES_INSTALL_DIR}/korganizer )

install( FILES
    korganizer.kcfg
  DESTINATION ${KCFG_INSTALL_DIR} )

install( FILES
    korganizer.upd
  DESTINATION ${KCONF_UPDATE_INSTALL_DIR} )

install( FILES
    tips korganizerui.rc korganizer_part.rc
  DESTINATION ${DATA_INSTALL_DIR}/korganizer )

install( PROGRAMS
    ${CMAKE_CURRENT_BINARY_DIR}/ical2vcal
  DESTINATION ${BIN_INSTALL_DIR} )


##### korganizer (executable) ###################

kde_add_executable( korganizer AUTOMOC
  SOURCES main.cpp korganizer.cpp koapp.cpp
  LINK korganizer-shared
  DESTINATION ${BIN_INSTALL_DIR}
)


##### kcm_korganizer (module) ###################

kde_add_kpart( kcm_korganizer AUTOMOC
  SOURCES koprefsdialog.cpp
  LINK korganizer-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### libkorganizerpart (module) ################

kde_add_kpart( libkorganizerpart AUTOMOC
  SOURCES korganizer_part.cpp
  LINK korganizer-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### korganizer_calendar (shared) ##############

kde_add_library( korganizer_calendar SHARED
  SOURCES stdcalendar.cpp
  VERSION 1.0.0
  LINK kdepim-shared kcal-shared
  DESTINATION ${LIB_INSTALL_DIR}
)


##### korganizer_eventviewer (shared) ###########

set( target korganizer_eventviewer )

set( ${target}_SRCS
  koeventviewer.cpp urihandler.cpp koeventviewerdialog.cpp ../kmail/kmailIface.stub_ng )

kde_add_library( ${target} SHARED AUTOMOC
  SOURCES ${${target}_SRCS}
  VERSION 1.0.0
  LINK kcal-shared
  DESTINATION ${LIB_INSTALL_DIR}
)


##### korganizer (shared) #######################

add_custom_command( OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/libkcal/htmlexportsettings.h
  COMMAND
    mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/libkcal
  COMMAND ${KDE_KCFGC_EXECUTABLE}
    -d ${CMAKE_CURRENT_BINARY_DIR}/libkcal
    ${CMAKE_SOURCE_DIR}/libkcal/htmlexportsettings.kcfg
    ${CMAKE_SOURCE_DIR}/libkcal/htmlexportsettings.kcfgc
  DEPENDS
    ${CMAKE_SOURCE_DIR}/libkcal/htmlexportsettings.kcfg
    ${CMAKE_SOURCE_DIR}/libkcal/htmlexportsettings.kcfgc
)

set_source_files_properties( calendarview.cpp
  PROPERTIES OBJECT_DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/libkcal/htmlexportsettings.h )

kde_add_library( korganizer SHARED AUTOMOC
  META_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/interfaces/korganizer
  SOURCES
    komessagebox.cpp koagendaview.cpp koagenda.cpp koagendaitem.cpp
    datenavigator.cpp kdatenavigator.cpp datenavigatorcontainer.cpp
    datechecker.cpp komonthview.cpp searchdialog.cpp calendarview.cpp
    koviewmanager.cpp kodialogmanager.cpp archivedialog.cpp kohelper.cpp
    komailclient.cpp kotodoview.cpp kotodoviewitem.cpp kolistview.cpp
    koincidenceeditor.cpp koeventeditor.cpp kotodoeditor.cpp kojournaleditor.cpp
    koprefs.cpp kowindowlist.cpp koeditorgeneral.cpp koeditorgeneralevent.cpp
    koeditorgeneraltodo.cpp koeditorgeneraljournal.cpp koeditordetails.cpp
    koeditoralarms_base.ui koeditoralarms.cpp koeditorrecurrence.cpp
    koeditorattachments.cpp kogroupwareprefspage.ui koeventpopupmenu.cpp
    koeditorfreebusy.cpp publishdialog_base.ui publishdialog.cpp
    koeventview.cpp korganizeriface.skel kcalendariface.skel filtereditdialog.cpp
    filteredit_base.ui kowhatsnextview.cpp kojournalview.cpp journalentry.cpp
    kocore.cpp mailscheduler.cpp kodaymatrix.cpp docprefs.cpp statusdialog.cpp
    koglobals.cpp konewstuff.cpp actionmanager.cpp resourceview.cpp
    navigatorbar.cpp kogroupware.cpp history.cpp koprefs_base.kcfgc
    koincidencetooltip.cpp aboutdata.cpp importdialog.cpp
    korganizerifaceimpl.cpp freebusymanager.cpp freebusyurldialog.cpp
    eventarchiver.cpp koidentitymanager.cpp exportwebdialog.cpp
    kocorehelper.cpp incidencechanger.cpp template_management_dialog_base.ui
    templatemanagementdialog.cpp agendaview.cpp multiagendaview.cpp
    timelineitem.cpp kotimelineview.cpp koattendeeeditor.cpp timelabels.cpp
  VERSION 1.0.0
  LINK
    kdgantt-static
    korganizer_eventviewer-shared korganizer_calendar-shared korg_stdprinting-shared
    kholidays-shared kpimidentities-shared
    kutils-shared knewstuff-shared
  DESTINATION ${LIB_INSTALL_DIR}
)


##### install import cmake modules ###############

kde_install_export( )
