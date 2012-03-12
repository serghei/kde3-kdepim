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

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/../../interfaces
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)

link_directories(
  ${QT_LIBRARY_DIR}
)


##### other data ################################

install( FILES kcmkontactknt.desktop DESTINATION ${SERVICES_INSTALL_DIR} )
install( FILES newstickerplugin.desktop DESTINATION ${SERVICES_INSTALL_DIR}/kontact )


##### libkontact_newstickerplugin (module) ######

kde_add_kpart( libkontact_newstickerplugin AUTOMOC
  SOURCES
    newsticker_plugin.cpp summarywidget.cpp summarywidget.skel
  LINK kpinterfaces-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### kcm_kontactknt (module) ###################

kde_add_kpart( kcm_kontactknt AUTOMOC
  SOURCES kcmkontactknt.cpp
  LINK kdeui-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)
