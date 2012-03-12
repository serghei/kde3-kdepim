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

add_subdirectory( about )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/../interfaces
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)

link_directories(
  ${QT_LIBRARY_DIR}
)


##### other data ################################

kde_install_icons( )
install( FILES Kontact.desktop kontactdcop.desktop DESTINATION ${XDG_APPS_INSTALL_DIR} )
install( FILES kontact.kcfg DESTINATION ${KCFG_INSTALL_DIR} )
install( FILES kontactconfig.desktop DESTINATION ${SERVICES_INSTALL_DIR} )
install( FILES kontactui.rc kontact.setdlg DESTINATION ${DATA_INSTALL_DIR}/kontact )


##### kcm_kontact (module) ######################

kde_add_kpart( kcm_kontact AUTOMOC
  SOURCES kcmkontact.cpp
  LINK kontact-shared kdepim-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### kontact (executable) ######################

kde_add_executable( kontact AUTOMOC
  SOURCES
    main.cpp mainwindow.cpp sidepanebase.cpp iconsidepane.cpp
    aboutdialog.cpp profilemanager.cpp profiledialog.cpp
    kontactiface.skel
  LINK kontact-shared kpinterfaces-shared kutils-shared khtml-shared
  DESTINATION ${BIN_INSTALL_DIR}
)


##### kontact (shared) ##########################

kde_add_library( kontact SHARED
  SOURCES prefs.kcfgc
  VERSION 1.0.0
  LINK kdecore-shared
  DESTINATION ${LIB_INSTALL_DIR}
)
