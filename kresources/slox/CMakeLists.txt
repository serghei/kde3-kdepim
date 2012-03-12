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


##### other data ################################

install( FILES kcal_slox.desktop kcal_ox.desktop DESTINATION ${SERVICES_INSTALL_DIR}/kresources/kcal )
install( FILES kabc_slox.desktop kabc_ox.desktop DESTINATION ${SERVICES_INSTALL_DIR}/kresources/kabc )


##### kcal_slox (module) ########################

kde_add_kpart( kcal_slox AUTOMOC
  SOURCES kcalresourceslox_plugin.cpp
  LINK kcal_slox-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### kabc_slox (module) ########################

kde_add_kpart( kabc_slox AUTOMOC
  SOURCES kabcresourceslox_plugin.cpp
  LINK kabc_slox-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### kslox (shared) ############################

kde_add_library( kslox SHARED AUTOMOC
  SOURCES
    sloxaccounts.cpp webdavhandler.cpp sloxfolder.cpp sloxfoldermanager.cpp
    sloxfolderdialog.cpp sloxbase.cpp
  VERSION 0.0.0
  LINK kdepim-shared
  DESTINATION ${LIB_INSTALL_DIR}
)


##### kabc_slox (shared) ########################

kde_add_library( kabc_slox SHARED AUTOMOC
  SOURCES
    kabcresourceslox.cpp kabcresourcesloxconfig.cpp kabcsloxprefs.kcfgc
  VERSION 0.0.0
  LINK kslox-shared
  DESTINATION ${LIB_INSTALL_DIR}
)


##### kcal_slox (shared) ########################

kde_add_library( kcal_slox SHARED AUTOMOC
  SOURCES
    kcalresourceslox.cpp kcalresourcesloxconfig.cpp kcalsloxprefs.kcfgc
  VERSION 0.0.0
  LINK kslox-shared
  DESTINATION ${LIB_INSTALL_DIR}
)
