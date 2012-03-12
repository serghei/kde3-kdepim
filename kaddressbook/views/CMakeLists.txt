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
  ${CMAKE_BINARY_DIR}/kaddressbook/common
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/kaddressbook
  ${CMAKE_SOURCE_DIR}/kaddressbook/interfaces
  ${CMAKE_SOURCE_DIR}/kaddressbook/common
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

install( FILES
    cardview.desktop iconview.desktop tableview.desktop
  DESTINATION ${SERVICES_INSTALL_DIR}/kaddressbook )


##### libkaddrbk_cardview (module) ##############

kde_add_kpart( libkaddrbk_cardview AUTOMOC
  SOURCES
    cardview.cpp colorlistbox.cpp configurecardviewdialog.cpp
    kaddressbookcardview.cpp
  LINK kaddressbook-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### libkaddrbk_iconview (module) ##############

kde_add_kpart( libkaddrbk_iconview AUTOMOC
  SOURCES
    kaddressbookiconview.cpp
  LINK kaddressbook-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### libkaddrbk_tableview (module) #############

kde_add_kpart( libkaddrbk_tableview AUTOMOC
  SOURCES
    configuretableviewdialog.cpp contactlistview.cpp
    kaddressbooktableview.cpp
  LINK kaddressbook-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)
