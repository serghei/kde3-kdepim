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

add_definitions( -DLIBKLEOPATRA_NO_COMPAT )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_BINARY_DIR}/certmanager/lib/ui
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/certmanager/lib
  ${CMAKE_SOURCE_DIR}/certmanager/lib/ui
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

install( FILES
    kleopatra_config_dirserv.desktop
    kleopatra_config_appear.desktop
    kleopatra_config_dnorder.desktop
  DESTINATION ${SERVICES_INSTALL_DIR} )


##### kcm_kleopatra (module) ####################

kde_add_kpart( kcm_kleopatra AUTOMOC
  SOURCES
    dirservconfigpage.cpp appearanceconfigpage.cpp
    appearanceconfigwidgetbase.ui dnorderconfigpage.cpp
    appearanceconfigwidget.cpp
  LINK kleopatra-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### conf (static) #############################

kde_add_library( conf STATIC AUTOMOC
  SOURCES configuredialog.cpp
)
