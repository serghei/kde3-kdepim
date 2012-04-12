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
  ${CMAKE_CURRENT_SOURCE_DIR}/../../lib
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### resourcescalixshared (static) #############

kde_add_library( resourcescalixshared STATIC_PIC AUTOMOC
  SOURCES
    resourcescalixbase.cpp kmailconnection.cpp scalixbase.cpp
    subresource.cpp kmailconnection.skel_ng
    ${CMAKE_SOURCE_DIR}/kmail/kmailicalIface.stub_ng
)
