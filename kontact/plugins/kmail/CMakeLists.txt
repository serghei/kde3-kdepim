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
  ${CMAKE_CURRENT_SOURCE_DIR}/../../interfaces
  ${CMAKE_BINARY_DIR}
#   ${CMAKE_BINARY_DIR}/kmail
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${CMAKE_SOURCE_DIR}/kmail
  ${CMAKE_SOURCE_DIR}/certmanager/lib
  ${CMAKE_SOURCE_DIR}/libkdenetwork
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
  ${GPGME_INCLUDE_DIRS}
)

link_directories(
  ${QT_LIBRARY_DIR}
)


##### other data ################################

install( FILES kcmkmailsummary.desktop DESTINATION ${SERVICES_INSTALL_DIR} )
install( FILES kmailplugin.desktop DESTINATION ${SERVICES_INSTALL_DIR}/kontact )


##### libkontact_kmailplugin (module) ###########

# FIXME please review this

kde_add_kpart( libkontact_kmailplugin AUTOMOC
  SOURCES
    kmail_plugin.cpp summarywidget.cpp summarywidget.skel_ng
    ../../../kmail/templatesinsertcommand.cpp
    ../../../kmail/globalsettings.cpp
    ../../../kmail/replyphrases.kcfgc
    ../../../kmail/templatesconfiguration_kfg.kcfgc
    ../../../kmail/templatesconfiguration.cpp
    ../../../kmail/templatesconfiguration_base.ui
    ../../../kmail/kmailIface.stub_ng
    ../../../kmail/globalsettings_base.kcfgc
  LINK kpinterfaces-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### kcm_kmailsummary (module) #################

kde_add_kpart( kcm_kmailsummary AUTOMOC
  SOURCES kcmkmailsummary.cpp
  LINK kdeui-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)
