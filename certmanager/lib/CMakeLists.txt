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

add_subdirectory( pics )
add_subdirectory( kleo )
add_subdirectory( backends )
add_subdirectory( ui )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${CMAKE_SOURCE_DIR}/libkdenetwork
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
  ${GPGME_INCLUDE_DIRS}
)


##### other data ################################

install( FILES libkleopatrarc.desktop DESTINATION ${CONFIG_INSTALL_DIR} RENAME libkleopatrarc )


##### kleopatra (shared) ########################

kde_add_library( kleopatra SHARED AUTOMOC
  SOURCES
    cryptplug.cpp cryptplugwrapper.cpp
    cryptplugwrapperlist.cpp cryptplugfactory.cpp
  VERSION 1.0.0
  EMBED
    kleopatra_core-static kleopatra_ui-static
  LINK
    kleopatra_backend_qgpgme-static
    kleopatra_backend_chiasmus-static
    qgpgme-shared kio-shared
  DESTINATION ${LIB_INSTALL_DIR}
)
