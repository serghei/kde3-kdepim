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

add_subdirectory( devices )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

kde_install_icons( kmobile )
install( FILES kmobile.desktop DESTINATION ${XDG_APPS_INSTALL_DIR} )
install( FILES libkmobile.desktop DESTINATION ${SERVICETYPES_INSTALL_DIR} )
install( FILES kmobileui.rc DESTINATION ${DATA_INSTALL_DIR}/kmobile )


##### kmobile (executable) ######################

kde_add_executable( kmobile AUTOMOC
  SOURCES
    main.cpp kmobile.cpp kmobileview.cpp kmobileitem.cpp pref.cpp
    kmobileiface.skel kmobile_selectiondialog.ui systemtray.cpp
  LINK kmobiledevice-shared
  DESTINATION ${BIN_INSTALL_DIR}
)


##### kmobiledevice (shared) ####################

kde_add_library( kmobiledevice SHARED AUTOMOC
  SOURCES kmobiledevice.cpp
  LINK kcal-shared
  DESTINATION ${LIB_INSTALL_DIR}
)


##### kmobileclient (shared) ####################

kde_add_library( kmobileclient SHARED AUTOMOC
  SOURCES kmobileclient.cpp
  LINK kdecore-shared
  DESTINATION ${LIB_INSTALL_DIR}
)
