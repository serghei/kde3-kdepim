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

add_definitions( -DQT_PLUGIN )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### kpartsdesignerplugin (module) #############

kde_add_kpart( kpartsdesignerplugin AUTOMOC
  SOURCES kpartsdesignerplugin.cpp
  LINK kparts-shared kio-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}/plugins/designer
)
