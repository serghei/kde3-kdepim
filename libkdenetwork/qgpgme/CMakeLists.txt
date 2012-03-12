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
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/libkdenetwork
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### headers ###################################

install( FILES
    eventloopinteractor.h dataprovider.h
  DESTINATION ${INCLUDE_INSTALL_DIR}/qgpgme )


##### qgpgme (shared) ###########################

kde_add_library( qgpgme SHARED AUTOMOC
  SOURCES
    eventloopinteractor.cpp dataprovider.cpp
  VERSION 0.0.0
  LINK gpgme++-shared ${TQT_LIBRARIES}
  DESTINATION ${LIB_INSTALL_DIR}
)
