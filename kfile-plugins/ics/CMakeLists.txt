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

kde_import( libkmime )
kde_import( ktnef )
kde_import( libkcal )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

install( FILES kfile_ics.desktop DESTINATION ${SERVICES_INSTALL_DIR} )


##### kfile_ics (module) ########################

kde_add_kpart( kfile_ics AUTOMOC
  SOURCES kfile_ics.cpp
  LINK kcal-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)
