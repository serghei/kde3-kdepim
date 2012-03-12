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

kde_import( libkmime )
kde_import( ktnef )
kde_import( libkcal )
kde_import( libkdepim )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

install( FILES kandy.desktop DESTINATION ${XDG_APPS_INSTALL_DIR} )
install( FILES uninstall.desktop RENAME kandy.desktop DESTINATION ${APPS_INSTALL_DIR}/Utilities )
install( FILES kandy.kcfg DESTINATION ${KCFG_INSTALL_DIR} )
install( FILES kandyui.rc kandymobileui.rc DESTINATION ${DATA_INSTALL_DIR}/kandy )


##### kandy (executable) ########################

kde_add_executable( kandy AUTOMOC
  SOURCES
    main.cpp kandy.cpp cmdpropertiesdialog_base.ui
    cmdpropertiesdialog.cpp kandyview.cpp kandyiface.skel modem.cpp
    atcommand.cpp commanditem.cpp mobilegui_base.ui mobilegui.cpp
    commandscheduler.cpp commandset.cpp kandyprefs.kcfgc
    kandyprefsdialog.cpp mobilemain.cpp
  LINK kdepim-shared ${LOCKDEV_LIBRARY}
  DESTINATION ${BIN_INSTALL_DIR}
)


##### kandy_client (executable) #################

kde_add_executable( kandy_client AUTOMOC
  SOURCES kandy_client.cpp
  LINK kdecore-shared
  DESTINATION ${BIN_INSTALL_DIR}
)
