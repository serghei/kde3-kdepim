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
  ${CMAKE_CURRENT_SOURCE_DIR}/../shared
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

install(
  FILES kolab.desktop
  DESTINATION ${SERVICES_INSTALL_DIR}/kresources/kabc )

install(
  FILES ${CMAKE_CURRENT_SOURCE_DIR}/../uninstall.desktop
  DESTINATION ${SERVICES_INSTALL_DIR}/kresources/kabc
  RENAME imap.desktop )


##### kabc_kolab (module) #######################

kde_add_kpart( kabc_kolab AUTOMOC
  SOURCES resourcekolab_plugin.cpp
  LINK kabckolab-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### kabckolab (shared) ########################

kde_add_library( kabckolab SHARED AUTOMOC
  SOURCES resourcekolab.cpp contact.cpp
  VERSION 0.0.0
  LINK resourcekolabshared-static kgroupwarebase-shared
  DESTINATION ${LIB_INSTALL_DIR}
)
