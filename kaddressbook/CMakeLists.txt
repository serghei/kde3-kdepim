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

kde_import( libkdenetwork )
kde_import( certmanager )
kde_import( libkmime )
kde_import( ktnef )
kde_import( libkcal )
kde_import( libkdepim )

add_subdirectory( interfaces )
add_subdirectory( printing )
add_subdirectory( editors )
add_subdirectory( views )
add_subdirectory( features )
add_subdirectory( xxport )
add_subdirectory( kcmconfigs )
add_subdirectory( pics )
add_subdirectory( csv-templates )
add_subdirectory( thumbnailcreator )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}/common
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/common
  ${CMAKE_CURRENT_SOURCE_DIR}/interfaces
  ${CMAKE_CURRENT_SOURCE_DIR}/editors
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

kde_install_icons( kaddressbook )

install( FILES
    kaddressbook.desktop
  DESTINATION ${XDG_APPS_INSTALL_DIR} )

install( FILES
    kaddressbook_view.desktop dcopaddressbook.desktop
  DESTINATION ${SERVICETYPES_INSTALL_DIR} )

install( FILES
    kaddressbookui.rc kaddressbook_part.rc zone.tab
  DESTINATION ${DATA_INSTALL_DIR}/kaddressbook )


##### libkaddressbookpart (module) ##############

kde_add_kpart( libkaddressbookpart AUTOMOC
  SOURCES kaddressbook_part.cpp
  LINK kaddressbook-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### kaddressbook (executable) #################

kde_add_executable( kaddressbook AUTOMOC
  SOURCES main.cpp kaddressbookmain.cpp
  LINK kaddressbook-shared
  DESTINATION ${BIN_INSTALL_DIR}
)


##### kaddressbook (shared) #####################

kde_add_library( kaddressbook SHARED AUTOMOC
  SOURCES
    addresseeconfig.cpp addresseeeditordialog.cpp addresseeeditorwidget.cpp
    addresseeeditorbase.cpp addresseeeditorextension.cpp addresseeutil.cpp
    addresseditwidget.cpp addviewdialog.cpp emaileditwidget.cpp
    extensionmanager.cpp filtereditdialog.cpp filterselectionwidget.cpp
    geowidget.cpp imagewidget.cpp incsearchwidget.cpp jumpbuttonbar.cpp kabcore.cpp
    kablock.cpp kaddressbookiface.skel kaddressbookservice.cpp kaddressbookview.cpp
    keywidget.cpp ldapsearchdialog.cpp nameeditdialog.cpp phoneeditwidget.cpp
    secrecywidget.cpp soundwidget.cpp viewconfigurefieldspage.cpp
    viewconfigurefilterpage.cpp viewconfigurewidget.cpp undocmds.cpp
    viewmanager.cpp xxportmanager.cpp xxportselectdialog.cpp
    contacteditorwidgetmanager.cpp simpleaddresseeeditor.cpp
    advancedcustomfields.cpp customfieldswidget.cpp freebusywidget.cpp
    searchmanager.cpp imeditwidget.cpp kabtools.cpp distributionlistpicker.cpp
    distributionlisteditor.cpp distributionlistentryview.cpp
  VERSION 0.0.0
  LINK
    kabcommon-static kabim-static printer-static
    kabinterfaces-shared
    kdepim-shared kabc_file-shared kdeprint-shared kutils-shared
  DESTINATION ${LIB_INSTALL_DIR}
)
