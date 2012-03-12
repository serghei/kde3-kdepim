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

install( FILES karmplugin.desktop DESTINATION ${SERVICES_INSTALL_DIR}/kontact )


##### libkontact_karm (module) ##################

kde_add_kpart( libkontact_karm AUTOMOC
  SOURCES
    karm_plugin.cpp ${CMAKE_SOURCE_DIR}/karm/karmdcopiface.stub
  LINK kpinterfaces-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)
