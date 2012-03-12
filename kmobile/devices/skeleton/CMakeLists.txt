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
  ${CMAKE_CURRENT_SOURCE_DIR}/../..
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

install( FILES
    libkmobile_skeleton.desktop
  DESTINATION ${SERVICES_INSTALL_DIR} )


##### libkmobile_skeleton (module) ##############

kde_add_kpart( libkmobile_skeleton AUTOMOC
  SOURCES skeleton.cpp
  LINK kmobiledevice-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)
