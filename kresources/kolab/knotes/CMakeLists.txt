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
  ${CMAKE_SOURCE_DIR}/knotes
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

install(
  FILES kolabresource.desktop
  DESTINATION ${SERVICES_INSTALL_DIR}/kresources/knotes )

install(
  FILES ${CMAKE_CURRENT_SOURCE_DIR}/../uninstall.desktop
  DESTINATION ${SERVICES_INSTALL_DIR}/kresources/knotes
  RENAME imap.desktop )


##### knotes_kolab (module) #####################

kde_add_kpart( knotes_kolab AUTOMOC
  SOURCES resourcekolab_plugin.cpp
  LINK knoteskolab-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### knoteskolab (shared) ######################

kde_add_library( knoteskolab SHARED AUTOMOC
  SOURCES resourcekolab.cpp note.cpp
  VERSION 0.0.0
  LINK resourcekolabshared-static kgroupwarebase-shared knotes-shared
  DESTINATION ${LIB_INSTALL_DIR}
)
