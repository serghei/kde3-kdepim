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
  ${CMAKE_SOURCE_DIR}/korganizer/interfaces
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)

link_directories(
  ${QT_LIBRARY_DIR}
)


##### headers ###################################

install( FILES
    calprintpluginbase.h calprinter.h
  DESTINATION ${INCLUDE_INSTALL_DIR}/korganizer )


##### kocorehelper (shared) #####################

kde_add_library( kocorehelper SHARED
  SOURCES cellitem.cpp
  VERSION 1.0.0
  LINK kdepim-shared
  DESTINATION ${LIB_INSTALL_DIR}
)


##### korg_stdprinting (shared) #################

kde_add_library( korg_stdprinting SHARED AUTOMOC
  SOURCES
    calprinter.cpp calprintpluginbase.cpp calprintdefaultplugins.cpp
    calprintdayconfig_base.ui calprintmonthconfig_base.ui
    calprinttodoconfig_base.ui calprintweekconfig_base.ui
    calprintincidenceconfig_base.ui
  VERSION 1.0.0
  LINK kocorehelper-shared kdeprint-shared
  DESTINATION ${LIB_INSTALL_DIR}
)
