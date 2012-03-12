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
  ${CMAKE_SOURCE_DIR}/knotes
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

# FIXME this is a conflict

install(
  FILES scalix.desktop
  DESTINATION ${SERVICES_INSTALL_DIR}/kresources/knotes )

install(
  FILES ../uninstall.desktop
  RENAME scalix.desktop
  DESTINATION ${SERVICES_INSTALL_DIR}/kresources/knotes )


##### knotes_scalix (module) ####################

kde_add_kpart( knotes_scalix AUTOMOC
  SOURCES resourcescalix_plugin.cpp
  LINK knotesscalix-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### knotesscalix (shared) #####################

kde_add_library( knotesscalix SHARED AUTOMOC
  SOURCES resourcescalix.cpp
  VERSION 0.0.0
  LINK resourcescalixshared-static kgroupwarebase-shared knotes-shared
  DESTINATION ${LIB_INSTALL_DIR}
)
