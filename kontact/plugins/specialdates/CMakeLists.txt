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
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${CMAKE_SOURCE_DIR}
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)

link_directories(
  ${QT_LIBRARY_DIR}
)


##### other data ################################

install( FILES specialdatesplugin.desktop DESTINATION ${SERVICES_INSTALL_DIR}/kontact )
install( FILES kcmsdsummary.desktop DESTINATION ${SERVICES_INSTALL_DIR} )


##### libkontact_specialdatesplugin (module) ####

kde_add_kpart( libkontact_specialdatesplugin AUTOMOC
  SOURCES specialdates_plugin.cpp sdsummarywidget.cpp
  LINK kpinterfaces-shared kholidays-shared korganizer_calendar-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### kcm_sdsummary (module) ####################

kde_add_kpart( kcm_sdsummary AUTOMOC
  SOURCES kcmsdsummary.cpp
  LINK kdeui-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)
