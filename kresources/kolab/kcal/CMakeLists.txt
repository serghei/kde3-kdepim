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
  ${CMAKE_CURRENT_SOURCE_DIR}/../kcal
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

install(
  FILES kolab.desktop
  DESTINATION ${SERVICES_INSTALL_DIR}/kresources/kcal )

install(
  FILES ${CMAKE_CURRENT_SOURCE_DIR}/../uninstall.desktop
  DESTINATION ${SERVICES_INSTALL_DIR}/kresources/kcal
  RENAME imap.desktop)


##### kcal_kolab (module) #######################

kde_add_kpart( kcal_kolab AUTOMOC
  SOURCES
    resourcekolab_plugin.cpp
  LINK kcalkolab-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### kcalkolab (shared) ########################

kde_add_library( kcalkolab SHARED AUTOMOC
  SOURCES
    incidence.cpp event.cpp task.cpp journal.cpp resourcekolab.cpp
  VERSION 0.0.0
  LINK resourcekolabshared-static kgroupwarebase-shared
  DESTINATION ${LIB_INSTALL_DIR}
)
