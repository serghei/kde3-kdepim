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
  ${CMAKE_SOURCE_DIR}/korganizer/interfaces
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${CMAKE_SOURCE_DIR}/libkpimexchange/core
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

install( FILES exchange.desktop DESTINATION ${SERVICES_INSTALL_DIR}/korganizer )
install( FILES exchangeui.rc DESTINATION ${DATA_INSTALL_DIR}/korganizer/plugins )


##### libkorg_exchange (module) #################

kde_add_kpart( libkorg_exchange AUTOMOC
  SOURCES exchange.cpp exchangedialog.cpp exchangeconfig.cpp
  LINK korganizer-shared kpimexchange-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)
