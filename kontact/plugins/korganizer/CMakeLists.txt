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

kde_import( libkholidays )
kde_import( korganizer )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/../../interfaces
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/korganizer
  ${CMAKE_SOURCE_DIR}/korganizer/interfaces
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)

link_directories(
  ${QT_LIBRARY_DIR}
)


##### other data ################################

install( FILES
    korganizerplugin.desktop todoplugin.desktop journalplugin.desktop
  DESTINATION ${SERVICES_INSTALL_DIR}/kontact )

install( FILES
    kcmkorgsummary.desktop
  DESTINATION ${SERVICES_INSTALL_DIR} )


##### libkontact_korganizerplugin (module) ######

kde_add_kpart( libkontact_korganizerplugin AUTOMOC
  SOURCES
    korganizerplugin.cpp summarywidget.cpp
    ${CMAKE_SOURCE_DIR}/korganizer/kcalendariface.stub
    ${CMAKE_SOURCE_DIR}/korganizer/korganizeriface.stub
  LINK common-static kpinterfaces-shared korganizer_calendar-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### libkontact_todoplugin (module) ############

kde_add_kpart( libkontact_todoplugin AUTOMOC
  SOURCES
    todoplugin.cpp todosummarywidget.cpp
    ${CMAKE_SOURCE_DIR}/korganizer/kcalendariface.stub
    ${CMAKE_SOURCE_DIR}/korganizer/korganizeriface.stub
  LINK common-static kpinterfaces-shared korganizer-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### libkontact_journalplugin (module) #########

kde_add_kpart( libkontact_journalplugin AUTOMOC
  SOURCES
    journalplugin.cpp
    ${CMAKE_SOURCE_DIR}/korganizer/kcalendariface.stub
  LINK common-static kpinterfaces-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### kcm_korgsummary (module) ##################

kde_add_kpart( kcm_korgsummary AUTOMOC
  SOURCES kcmkorgsummary.cpp
  LINK kdeui-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### common (static) ###########################

kde_add_library( common STATIC_PIC
  SOURCES korg_uniqueapp.cpp
)
