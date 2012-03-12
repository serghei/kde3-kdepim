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

project( libkpimidentities )

kde_import( ktnef )
kde_import( libkmime )
kde_import( libkcal )
kde_import( libkdenetwork )
kde_import( certmanager )
kde_import( libkdepim )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${CMAKE_SOURCE_DIR}/certmanager/lib
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)

link_directories(
  ${QT_LIBRARY_DIR}
)


##### kpimidentities (shared) ###################

kde_add_library( kpimidentities SHARED AUTOMOC
  SOURCES
    identitymanager.cpp identity.cpp identitymanager.skel
    identitycombo.cpp
  VERSION 1.0.0
  LINK kleopatra-shared kdepim-shared
  DESTINATION ${LIB_INSTALL_DIR}
)

kde_install_export( )
