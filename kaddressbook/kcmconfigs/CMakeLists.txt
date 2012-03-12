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
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/kaddressbook/common
  ${CMAKE_SOURCE_DIR}/kaddressbook/interfaces
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

install( FILES
    kabconfig.desktop kabldapconfig.desktop kabcustomfields.desktop
  DESTINATION ${SERVICES_INSTALL_DIR} )


##### kcm_kabconfig (module) ####################

kde_add_kpart( kcm_kabconfig AUTOMOC
  SOURCES
    kcmkabconfig.cpp kabconfigwidget.cpp extensionconfigdialog.cpp
    addresseewidget.cpp
  LINK kabcommon-static kdepim-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### kcm_kabldapconfig (module) ################

kde_add_kpart( kcm_kabldapconfig AUTOMOC
  SOURCES
    addhostdialog.cpp kcmkabldapconfig.cpp ldapoptionswidget.cpp
  LINK kdepim-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### kcm_kabcustomfields (module) ##############

kde_add_kpart( kcm_kabcustomfields AUTOMOC
  SOURCES kcmkabcustomfields.cpp
  LINK kabcommon-static kdepim-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)
