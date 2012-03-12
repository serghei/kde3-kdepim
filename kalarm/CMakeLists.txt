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

kde_import( libkmime )
kde_import( ktnef )
kde_import( libkdepim )
kde_import( libkdenetwork )
kde_import( certmanager )
kde_import( libkcal )
kde_import( libkpimidentities )

add_subdirectory( kalarmd )
add_subdirectory( lib )
add_subdirectory( pixmaps )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/lib
  ${CMAKE_CURRENT_SOURCE_DIR}/kalarmd
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkmime
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${CMAKE_SOURCE_DIR}/certmanager/lib
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)

if( WITH_ARTS )
  set( ARTS_LIBRARIES artskde-shared mcop )
endif( )


##### other data ################################

kde_install_icons( )
install( FILES kalarm.desktop DESTINATION ${XDG_APPS_INSTALL_DIR} )
install( FILES kalarm.tray.desktop DESTINATION ${AUTOSTART_INSTALL_DIR} )
install( FILES kalarmui.rc DESTINATION ${DATA_INSTALL_DIR}/kalarm )
install( FILES uninstall.desktop DESTINATION ${APPS_INSTALL_DIR}/Applications RENAME kalarm.desktop )


##### kalarm (executable) #######################

kde_add_executable( kalarm AUTOMOC
  SOURCES
    birthdaydlg.cpp main.cpp alarmevent.cpp editdlg.cpp
    emailidcombo.cpp find.cpp pickfileradio.cpp
    calendarcompat.cpp eventlistviewbase.cpp alarmlistview.cpp
    kamail.cpp timeselector.cpp fontcolourbutton.cpp
    alarmtimewidget.cpp fontcolour.cpp soundpicker.cpp
    sounddlg.cpp alarmcalendar.cpp daemon.cpp undo.cpp
    kalarmapp.cpp mainwindowbase.cpp mainwindow.cpp
    messagewin.cpp preferences.cpp prefdlg.cpp
    kalarmiface.skel recurrenceedit.cpp karecurrence.cpp
    deferdlg.cpp functions.cpp specialactions.cpp reminder.cpp
    startdaytimer.cpp templatelistview.cpp templatepickdlg.cpp
    templatedlg.cpp templatemenuaction.cpp latecancel.cpp
    repetition.cpp alarmtext.cpp traywindow.cpp dcophandler.cpp
    kalarmd/alarmguiiface.skel
  LINK
    kalarm-static kalarmd-static
    kpimidentities-shared kutils-shared ${ARTS_LIBRARIES}
  DESTINATION ${BIN_INSTALL_DIR}
)
