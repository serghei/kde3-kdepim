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

include( ConfigureChecks.cmake )

add_definitions( "-DGPG_ERR_SOURCE_DEFAULT=((gpg_err_source_t)176)" )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/certmanager/lib
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${CMAKE_SOURCE_DIR}/libkdenetwork
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### kleopatra_backend_chiasmus (static) #######

kde_add_library( kleopatra_backend_chiasmus STATIC_PIC AUTOMOC
  SOURCES
    config_data.c obtainkeysjob.cpp symcryptrunprocessbase.cpp
    chiasmusjob.cpp chiasmuslibrary.cpp chiasmusbackend.cpp
)
