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
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### headers ###################################

install( FILES
    resourceremoteconfig.h resourceremote.h
  DESTINATION ${INCLUDE_INSTALL_DIR}/libkcal )


##### other data ################################

install( FILES
    remote.desktop
  DESTINATION ${SERVICES_INSTALL_DIR}/kresources/kcal )


##### kcal_remote (module) ######################

kde_add_kpart( kcal_remote AUTOMOC
  SOURCES resourceremote_plugin.cpp
  LINK kcal_resourceremote-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### kcal_resourceremote (shared) ##############

kde_add_library( kcal_resourceremote SHARED AUTOMOC
  SOURCES
    resourceremote.cpp resourceremoteconfig.cpp
  VERSION 1.0.0
  LINK kdepim-shared
  DESTINATION ${LIB_INSTALL_DIR}
)
