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
  ${CMAKE_BINARY_DIR}/kaddressbook/common
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/kaddressbook/common
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### headers ###################################

install( FILES
    resourcekabc.h resourcekabcconfig.h
  DESTINATION ${INCLUDE_INSTALL_DIR}/libkcal )


##### other data ################################

install( FILES kabc.desktop DESTINATION ${SERVICES_INSTALL_DIR}/kresources/kcal )


##### kcal_kabc (module) #######################

kde_add_kpart( kcal_kabc AUTOMOC
  SOURCES
    resourcekabc.cpp resourcekabcconfig.cpp
  LINK kabcommon-static kdepim-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)
