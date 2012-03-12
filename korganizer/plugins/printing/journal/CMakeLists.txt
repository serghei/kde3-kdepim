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
  ${CMAKE_SOURCE_DIR}/korganizer/interfaces/korganizer
  ${CMAKE_SOURCE_DIR}/korganizer/printing
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)

link_directories(
  ${QT_LIBRARY_DIR}
)


##### other data ################################

install( FILES journalprint.desktop DESTINATION ${SERVICES_INSTALL_DIR}/korganizer )


##### libkorg_journalprint (module) #############

kde_add_kpart( libkorg_journalprint AUTOMOC
  SOURCES
    calprintjournalconfig_base.ui journalprint.cpp
  LINK korg_stdprinting-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)
