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


##### other data ################################

install(
  FILES scalix.desktop
  DESTINATION ${SERVICES_INSTALL_DIR}/kresources/kcal )

install(
  FILES ../uninstall.desktop
  RENAME imap.desktop
  DESTINATION ${SERVICES_INSTALL_DIR}/kresources/kcal )


##### kcal_scalix (module) ######################

kde_add_kpart( kcal_scalix AUTOMOC
  SOURCES resourcescalix_plugin.cpp
  LINK kcalscalix-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### kcalscalix (shared) #######################

kde_add_library( kcalscalix SHARED AUTOMOC
  SOURCES resourcescalix.cpp
  VERSION 0.0.0
  LINK resourcescalixshared-static kgroupwarebase-shared
  DESTINATION ${LIB_INSTALL_DIR}
)
