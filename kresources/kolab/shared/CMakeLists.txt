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
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/kresources/lib
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### resourcekolabshared (static) ##############

set( KDE3_DCOPIDL_EXECUTABLE ${KDE3_DCOPIDLNG_EXECUTABLE} )

kde_add_library( resourcekolabshared STATIC_PIC AUTOMOC
  SOURCES
    resourcekolabbase.cpp kmailconnection.cpp kolabbase.cpp subresource.cpp
    kmailconnection.skel ${CMAKE_SOURCE_DIR}/kmail/kmailicalIface.stub
)
