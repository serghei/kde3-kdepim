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

# FIXME KDE_CXXFLAGS = -Wno-non-virtual-dtor

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/..
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### gwsoap (shared) ###########################

kde_add_library( gwsoap SHARED AUTOMOC
  SOURCES
    contactconverter.cpp gwconverter.cpp incidenceconverter.cpp groupwiseserver.cpp
    gwjobs.cpp ksslsocket.cpp soapC.cpp soapClient.cpp stdsoap2.cpp
  VERSION 0.0.0
  LINK kdepim-shared
  DESTINATION ${LIB_INSTALL_DIR}
)
