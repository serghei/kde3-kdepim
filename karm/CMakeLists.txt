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
kde_import( libkcal )
kde_import( libkdepim )
kde_import( kresources )

add_subdirectory( support )
add_subdirectory( pics )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkcal
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${CMAKE_SOURCE_DIR}/kresources/remote
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

kde_install_icons( karm )
install( FILES karm_part.desktop DESTINATION ${SERVICES_INSTALL_DIR} )
install( FILES uninstall.desktop RENAME karm.desktop DESTINATION ${APPS_INSTALL_DIR}/Utilities )
install( FILES karmui.rc DESTINATION ${DATA_INSTALL_DIR}/karm )
install( FILES karmui.rc DESTINATION ${DATA_INSTALL_DIR}/karmpart )


##### karm (shared) #############################

kde_add_library( karm SHARED AUTOMOC
  SOURCES
    kaccelmenuwatch.cpp desktoptracker.cpp edittaskdialog.cpp
    idletimedetector.cpp printdialog.cpp timekard.cpp karmutility.cpp
    ktimewidget.cpp karmstorage.cpp mainwindow.cpp preferences.cpp
    print.cpp task.cpp taskview.cpp tray.cpp csvexportdialog_base.ui
    csvexportdialog.cpp plannerparser.cpp karmdcopiface.skel
    taskviewwhatsthis.cpp
  VERSION 0.0.0
  LINK kcal_resourceremote-shared kdeprint-shared
  DESTINATION ${LIB_INSTALL_DIR}
)


##### libkarmpart (module) ######################

kde_add_kpart( libkarmpart AUTOMOC
  SOURCES karm_part.cpp
  LINK karm-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### karm (executable) #########################

kde_add_executable( karm
  SOURCES main.cpp
  LINK karm-shared
  DESTINATION ${BIN_INSTALL_DIR}
)
