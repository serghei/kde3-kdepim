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

add_subdirectory( pics )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/ktnef
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

install( FILES ktnef.desktop DESTINATION ${XDG_APPS_INSTALL_DIR} )
install( FILES ktnefui.rc DESTINATION ${DATA_INSTALL_DIR}/ktnef )
install( FILES ms-tnef.desktop DESTINATION ${MIME_INSTALL_DIR}/application )


##### ktnef (executable) ########################

kde_add_executable( ktnef AUTOMOC
  SOURCES
    ktnefmain.cpp ktnefview.cpp attachpropertydialogbase.ui
    attachpropertydialog.cpp messagepropertydialog.cpp
    qwmf.cpp main.cpp
  LINK ktnef-shared
  DESTINATION ${BIN_INSTALL_DIR}
)
