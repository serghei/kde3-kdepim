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

project( libkholidays )

add_subdirectory( holidays )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### kholidays (shared) ########################

kde_add_library( kholidays SHARED AUTOMOC
  SOURCES
    kholidays.cpp scanholiday.c parseholiday.h parseholiday.c lunarphase.cpp
  VERSION 1.0.0
  LINK kdecore-shared
  DESTINATION ${LIB_INSTALL_DIR}
)


##### install import cmake modules ###############

kde_install_export( )
