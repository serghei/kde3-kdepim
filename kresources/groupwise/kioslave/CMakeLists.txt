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
  ${CMAKE_CURRENT_SOURCE_DIR}/../soap
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

install( FILES
    groupwise.protocol groupwises.protocol
  DESTINATION ${SERVICES_INSTALL_DIR} )


##### kio_groupwise (module) ####################

kde_add_kpart( kio_groupwise AUTOMOC
  SOURCES groupwise.cpp
  LINK gwsoap-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)
