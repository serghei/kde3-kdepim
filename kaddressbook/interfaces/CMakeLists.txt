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
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### headers ###################################

install( FILES
    configurewidget.h contacteditorwidget.h core.h
    extensionwidget.h xxport.h
  DESTINATION ${INCLUDE_INSTALL_DIR}/kaddressbook )


##### other data ################################

install( FILES
    kaddressbook_contacteditorwidget.desktop
    kaddressbook_extension.desktop kaddressbook_xxport.desktop
  DESTINATION ${SERVICETYPES_INSTALL_DIR} )


##### kabinterfaces (shared) ####################

kde_add_library( kabinterfaces SHARED AUTOMOC
  SOURCES
    configurewidget.cpp contacteditorwidget.cpp
    core.cpp extensionwidget.cpp xxport.cpp
  VERSION 1.0.0
  LINK kabc-shared
  DESTINATION ${LIB_INSTALL_DIR}
)
