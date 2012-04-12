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

kde_import( knotes )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/../../interfaces
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)

link_directories(
  ${QT_LIBRARY_DIR}
)


##### other data ################################

install( FILES knotesplugin.desktop DESTINATION ${SERVICES_INSTALL_DIR}/kontact )
install( FILES knotes_part.rc DESTINATION ${DATA_INSTALL_DIR}/knotes )


##### libkontact_knotesplugin (module) ##########

kde_add_kpart( libkontact_knotesplugin AUTOMOC
  SOURCES
    knotes_plugin.cpp knotes_part.cpp summarywidget.cpp knotetip.cpp
    ${CMAKE_SOURCE_DIR}/knotes/KNotesIface.skel_ng
  LINK kpinterfaces-shared knotes-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)
