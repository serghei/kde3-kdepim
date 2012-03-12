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

project( certmanager )

include( ConfigureChecks.cmake )

kde_import( libkdenetwork )

add_subdirectory( lib )
add_subdirectory( conf )
add_subdirectory( kwatchgnupg )

add_definitions( -DLIBKLEOPATRA_NO_COMPAT )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/lib
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${CMAKE_SOURCE_DIR}/libkdenetwork
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

install( FILES kleopatra_import.desktop DESTINATION ${XDG_APPS_INSTALL_DIR} )
install( FILES kleopatraui.rc DESTINATION ${DATA_INSTALL_DIR}/kleopatra )


##### kleopatra (executable) ####################

kde_add_executable( kleopatra AUTOMOC
  SOURCES
    customactions.cpp aboutdata.cpp main.cpp certmanager.cpp
    hierarchyanalyser.cpp certificatewizard.ui certificatewizardimpl.cpp
    certificateinfowidget.ui certificateinfowidgetimpl.cpp
    crlview.cpp storedtransferjob.cpp certlistview.cpp
  LINK conf-static kleopatra-shared kutils-shared kabc-shared
  DESTINATION ${BIN_INSTALL_DIR}
)

kde_install_export( )
