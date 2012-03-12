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
  DESTINATION ${SERVICES_INSTALL_DIR}/kresources/kabc )

install(
  FILES ../uninstall.desktop
  RENAME imap.desktop
  DESTINATION ${SERVICES_INSTALL_DIR}/kresources/kabc )


##### kabc_scalix (module) ######################

kde_add_kpart( kabc_scalix AUTOMOC
  SOURCES resourcescalix_plugin.cpp
  LINK kabcscalix-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### kabcscalix (shared) #######################

kde_add_library( kabcscalix SHARED AUTOMOC
  SOURCES resourcescalix.cpp contact.cpp
  VERSION 0.0.0
  LINK resourcescalixshared-static kgroupwarebase-shared
  DESTINATION ${LIB_INSTALL_DIR}
)
