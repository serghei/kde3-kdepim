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
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${CMAKE_SOURCE_DIR}/libkmime
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### header files ################################

if( BUILD_LIBKDEPIM )
  install( FILES idmapper.h DESTINATION ${INCLUDE_INSTALL_DIR}/libemailfunctions )
endif()


##### emailfunctions (static) ###################

kde_add_library( emailfunctions STATIC_PIC AUTOMOC
  SOURCES
    email.cpp idmapper.cpp kasciistricmp.cpp
    kasciistringtools.cpp networkstatus.cpp networkstatus.skel
)
