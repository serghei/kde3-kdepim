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
  ${CMAKE_CURRENT_BINARY_DIR}/../lib
  ${CMAKE_CURRENT_SOURCE_DIR}/../lib
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

install( FILES kcal_groupdav.desktop DESTINATION ${SERVICES_INSTALL_DIR}/kresources/kcal )
install( FILES uninstall.desktop DESTINATION ${SERVICES_INSTALL_DIR}/kresources/kcal RENAME kcal_opengroupware.desktop )
install( FILES kabc_groupdav.desktop DESTINATION ${SERVICES_INSTALL_DIR}/kresources/kabc )
install( FILES uninstall.desktop DESTINATION ${SERVICES_INSTALL_DIR}/kresources/kabc RENAME kabc_opengroupware.desktop)


##### kcal_groupdav (module) ####################

kde_add_kpart( kcal_groupdav AUTOMOC
  SOURCES kcal_resourcegroupdav_plugin.cpp
  LINK kcal_groupdav-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### kabc_groupdav (module) ####################

kde_add_kpart( kabc_groupdav AUTOMOC
  SOURCES kabc_resourcegroupdav_plugin.cpp
  LINK kabc_groupdav-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### kgroupdav (static) ########################

kde_add_library( kgroupdav STATIC_PIC
  SOURCES groupdavglobals.cpp
)


##### kcal_groupdav (shared) ####################

kde_add_library( kcal_groupdav SHARED AUTOMOC
  SOURCES groupdavcalendaradaptor.cpp kcal_resourcegroupdav.cpp
  VERSION 1.0.0
  LINK kgroupdav-static kgroupwaredav-shared
  DESTINATION ${LIB_INSTALL_DIR}
)


##### kabc_groupdav (shared) ####################

kde_add_library( kabc_groupdav SHARED AUTOMOC
  SOURCES kabc_resourcegroupdav.cpp groupdavaddressbookadaptor.cpp
  VERSION 1.0.0
  LINK kgroupdav-static kgroupwaredav-shared
  DESTINATION ${LIB_INSTALL_DIR}
)
