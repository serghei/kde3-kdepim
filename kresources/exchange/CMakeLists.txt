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

kde_import( libkpimexchange )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${CMAKE_SOURCE_DIR}/libkpimexchange/core
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

install( FILES exchange.desktop DESTINATION ${SERVICES_INSTALL_DIR}/kresources/kcal )


##### resourcecalendarexchange (module) #########

kde_add_kpart( resourcecalendarexchange AUTOMOC
  SOURCES
    resourceexchange.cpp resourceexchangeconfig.cpp dateset.cpp
  LINK kpimexchange-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)
