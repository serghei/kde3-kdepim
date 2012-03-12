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

project( libkpgp )

add_subdirectory( pics )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

install( FILES kpgp.upd DESTINATION ${KCONF_UPDATE_INSTALL_DIR} )
install( PROGRAMS kpgp-3.1-upgrade-address-data.pl DESTINATION ${KCONF_UPDATE_INSTALL_DIR} )


##### kpgp (shared) #############################

kde_add_library( kpgp SHARED AUTOMOC
  SOURCES
    kpgpblock.cpp kpgpui.cpp kpgpkey.cpp kpgp.cpp kpgpbase.cpp
    kpgpbaseG.cpp kpgpbase2.cpp kpgpbase5.cpp kpgpbase6.cpp
  VERSION 2.2.0
  LINK kdeui-shared
  DESTINATION ${LIB_INSTALL_DIR}
)


kde_install_export( )
