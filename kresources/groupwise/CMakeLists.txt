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

add_subdirectory( soap )
add_subdirectory( kioslave )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

install( FILES kcal_groupwise.desktop DESTINATION ${SERVICES_INSTALL_DIR}/kresources/kcal )
install( FILES kabc_groupwise.desktop DESTINATION ${SERVICES_INSTALL_DIR}/kresources/kabc )


##### kcal_groupwise (module) ###################

kde_add_kpart( kcal_groupwise AUTOMOC
  SOURCES kcal_resourcegroupwise_plugin.cpp
  LINK kcal_groupwise-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### kabc_groupwise (module) ###################

kde_add_kpart( kabc_groupwise AUTOMOC
  SOURCES kabc_resourcegroupwise_plugin.cpp
  LINK kabc_groupwise-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### kcal_groupwise (shared) ###################

kde_add_library( kcal_groupwise SHARED AUTOMOC
  SOURCES
    kcal_resourcegroupwise.cpp kcal_resourcegroupwiseconfig.cpp
    kcal_groupwiseprefsbase.kcfgc kcal_groupwiseprefs.cpp
    groupwisesettingswidget.cpp groupwisesettingswidgetbase.ui
  VERSION 1.0.0
  LINK gwsoap-shared
  DESTINATION ${LIB_INSTALL_DIR}
)


##### kabc_groupwise (shared) ###################

kde_add_library( kabc_groupwise SHARED AUTOMOC
  SOURCES
    kabc_resourcegroupwise.cpp kabc_resourcegroupwiseconfig.cpp
    kabc_groupwiseprefs.kcfgc
  VERSION 1.0.0
  LINK gwsoap-shared
  DESTINATION ${LIB_INSTALL_DIR}
)
