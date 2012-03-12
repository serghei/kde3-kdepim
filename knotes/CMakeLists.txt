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

project( knotes )

kde_import( libkmime )
kde_import( ktnef )
kde_import( libkcal )
kde_import( libkdepim )

add_subdirectory( pics )
add_subdirectory( icons )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)

link_directories(
  ${QT_LIBRARY_DIR}
)


##### headers ###################################

install( FILES KNotesIface.h KNotesAppIface.h DESTINATION ${INCLUDE_INSTALL_DIR} )


##### other data ################################

install( FILES knotes.desktop DESTINATION ${XDG_APPS_INSTALL_DIR} )
install( FILES knoteconfig.kcfg knotesglobalconfig.kcfg DESTINATION ${KCFG_INSTALL_DIR} )
install( FILES knotesappui.rc knotesui.rc DESTINATION ${DATA_INSTALL_DIR}/knotes )
install( FILES local.desktop DESTINATION ${SERVICES_INSTALL_DIR}/kresources/knotes )
install( FILES knotes_manager.desktop DESTINATION ${SERVICES_INSTALL_DIR}/kresources )


##### knotes (executable) #######################

kde_add_executable( knotes AUTOMOC
  SOURCES
    main.cpp knotesapp.cpp KNotesAppIface.skel
  LINK knotes-shared
  DESTINATION ${BIN_INSTALL_DIR}
)


##### knotes_local (module) #####################

kde_add_kpart( knotes_local AUTOMOC
  SOURCES
    resourcelocal_plugin.cpp
  LINK knotes-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### knotes (shared) ###########################

kde_add_library( knotes SHARED AUTOMOC
  SOURCES
    knoteslegacy.cpp knoteconfig.kcfgc knotesglobalconfig.kcfgc knoteedit.cpp
    knoteprinter.cpp knotesnetrecv.cpp knotesnetsend.cpp resourcemanager.cpp
    resourcenotes.cpp resourcelocal.cpp resourcelocalconfig.cpp knote.cpp
    knotebutton.cpp knoteconfigdlg.cpp knotehostdlg.cpp knotealarmdlg.cpp
    knotesalarm.cpp
  VERSION 0.0.0
  LINK kdepim-shared kutils-shared kdeprint-shared
  DESTINATION ${LIB_INSTALL_DIR}
)


##### install import cmake modules ###############

kde_install_export( )
