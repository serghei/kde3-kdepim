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
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)

link_directories(
  ${QT_LIBRARY_DIR}
)


##### headers ###################################

install( FILES
    core.h plugin.h summary.h
  DESTINATION ${INCLUDE_INSTALL_DIR}/kontact )


##### other data ################################

install( FILES
    kontactplugin.desktop
  DESTINATION ${SERVICETYPES_INSTALL_DIR} )


##### kpinterfaces (shared) #########################

kde_add_library( kpinterfaces SHARED AUTOMOC
  SOURCES
    core.cpp plugin.cpp summary.cpp uniqueapphandler.cpp
  VERSION 1.0.0
  LINK kdepim-shared
  DESTINATION ${LIB_INSTALL_DIR}
)
