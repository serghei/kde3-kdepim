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

include_directories(
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/ktnef
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### ktnef (shared) ############################

kde_add_library( ktnef SHARED
  SOURCES
    ktnefparser.cpp ktnefproperty.cpp ktnefattach.cpp
    mapi.cpp ktnefpropertyset.cpp ktnefmessage.cpp
    ktnefwriter.cpp lzfu.cpp
  VERSION 1.0.0
  LINK kio-shared
  DESTINATION ${LIB_INSTALL_DIR}
)
