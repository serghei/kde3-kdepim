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
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### headers ###################################

install( FILES
    kabc_resourcexmlrpc.h kcal_resourcexmlrpc.h
  DESTINATION ${INCLUDE_INSTALL_DIR}/kabc )


##### other data ################################

install( FILES kabc_xmlrpc.desktop DESTINATION ${SERVICES_INSTALL_DIR}/kresources/kabc )
install( FILES kcal_xmlrpc.desktop DESTINATION ${SERVICES_INSTALL_DIR}/kresources/kcal )
install( FILES knotes_xmlrpc.desktop DESTINATION ${SERVICES_INSTALL_DIR}/kresources/knotes )


##### egwcommon (static) ########################

kde_add_library( egwcommon STATIC_PIC AUTOMOC
  SOURCES
    xmlrpciface.cpp synchronizer.cpp debugdialog.cpp
)


##### kabc_xmlrpc (shared) ######################

kde_add_library( kabc_xmlrpc SHARED AUTOMOC
  SOURCES
    kabc_resourcexmlrpc.cpp kabc_resourcexmlrpcconfig.cpp
    kabc_egroupwareprefs.kcfgc
  VERSION 1.0.0
  LINK egwcommon-static kabcommon-static kdepim-shared
  DESTINATION ${LIB_INSTALL_DIR}
)


##### kcal_xmlrpc (shared) ######################

kde_add_library( kcal_xmlrpc SHARED AUTOMOC
  SOURCES
    kcal_resourcexmlrpc.cpp kcal_resourcexmlrpcconfig.cpp todostatemapper.cpp
    kcal_egroupwareprefs.kcfgc
  VERSION 1.0.0
  LINK egwcommon-static kdepim-shared
  DESTINATION ${LIB_INSTALL_DIR}
)


##### knotes_xmlrpc (shared) ####################

kde_add_library( knotes_xmlrpc SHARED AUTOMOC
  SOURCES
    knotes_resourcexmlrpc.cpp knotes_resourcexmlrpcconfig.cpp
    knotes_egroupwareprefs.kcfgc
  VERSION 1.0.0
  LINK egwcommon-static knotes-shared
  DESTINATION ${LIB_INSTALL_DIR}
)


##### kabc_xmlrpc (module) ######################

kde_add_kpart( kabc_xmlrpc AUTOMOC
  SOURCES kabc_resourcexmlrpcplugin.cpp
  LINK kabc_xmlrpc-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### kcal_xmlrpc (module) ######################

kde_add_kpart( kcal_xmlrpc AUTOMOC
  SOURCES kcal_resourcexmlrpcplugin.cpp
  LINK kcal_xmlrpc-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### knotes_xmlrpc (module) ####################

kde_add_kpart( knotes_xmlrpc AUTOMOC
  SOURCES knotes_resourcexmlrpcplugin.cpp
  LINK knotes_xmlrpc-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)
