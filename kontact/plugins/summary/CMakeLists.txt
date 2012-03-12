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
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/certmanager/lib
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)

link_directories(
  ${QT_LIBRARY_DIR}
)


##### other data ################################

install( FILES kcmkontactsummary.desktop DESTINATION ${SERVICES_INSTALL_DIR} )
install( FILES summaryplugin.desktop DESTINATION ${SERVICES_INSTALL_DIR}/kontact )
install( FILES kontactsummary_part.rc DESTINATION ${DATA_INSTALL_DIR}/kontactsummary )


##### libkontact_summaryplugin (module) #########

kde_add_kpart( libkontact_summaryplugin AUTOMOC
  SOURCES
    summaryview_plugin.cpp summaryview_part.cpp dropwidget.cpp
  LINK kpinterfaces-shared kdepim-shared kpimidentities-shared kutils-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### kcm_kontactsummary (module) ###############

kde_add_kpart( kcm_kontactsummary AUTOMOC
  SOURCES kcmkontactsummary.cpp
  LINK kdeui-shared kutils-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)
