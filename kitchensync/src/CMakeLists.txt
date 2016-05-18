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

add_subdirectory( about )
add_subdirectory( pics )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/..
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

install( FILES kitchensync.desktop DESTINATION ${XDG_APPS_INSTALL_DIR} )
install( FILES kitchensyncui.rc kitchensync_part.rc DESTINATION ${DATA_INSTALL_DIR}/kitchensync )


##### libkitchensyncpart (module) ###############

kde_add_kpart( libkitchensyncpart AUTOMOC
  SOURCES part.cpp
  LINK kitchensync-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)

##### kitchensync (executable) ##################

kde_add_executable( kitchensync AUTOMOC
  SOURCES main.cpp mainwindow.cpp
  LINK kitchensync-shared
  DESTINATION ${BIN_INSTALL_DIR}
)


##### kitchensync (shared) ######################

kde_add_library( kitchensync SHARED AUTOMOC
  SOURCES
    aboutpage.cpp mainwidget.cpp groupconfigdialog.cpp groupconfig.cpp
    groupitem.cpp groupview.cpp memberconfig.cpp syncprocess.cpp
    syncprocessmanager.cpp connectionwidgets.cpp pluginpicker.cpp
    configgui.cpp configguiblank.cpp configguifile.cpp memberinfo.cpp
    groupconfigcommon.cpp kwidgetlist.cpp configguipalm.cpp
    conflictdialog.cpp singleconflictdialog.cpp addresseediffalgo.cpp
    calendardiffalgo.cpp htmldiffalgodisplay.cpp genericdiffalgo.cpp
    multiconflictdialog.cpp configguiirmc.cpp configguisyncmlobex.cpp
    configguisyncmlhttp.cpp configguiopie.cpp
    configguigcalendar.cpp configguildap.cpp configguigpe.cpp
    configguijescs.cpp configguievo2.cpp configguimoto.cpp
    configguisynce.cpp configguisunbird.cpp
  VERSION 0.0.0
  LINK qopensync-shared kdepim-shared khtml-shared
  DESTINATION ${LIB_INSTALL_DIR}
)
