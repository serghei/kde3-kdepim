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

project( indexlib )

include( ConfigureChecks.cmake )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -include compat.h ${USE_EXCEPTIONS}" )

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_BINARY_DIR}
  ${KDE_INCLUDE_DIR}
)


##### headers ###################################

install( FILES
    create.h index.h lockfile.h
  DESTINATION ${INCLUDE_INSTALL_DIR}/index )


##### other data ################################

configure_file( indexlib-config.cmake indexlib-config @ONLY )

install( PROGRAMS
    ${CMAKE_CURRENT_BINARY_DIR}/indexlib-config
  DESTINATION ${BIN_INSTALL_DIR} )


##### index (shared) ############################

kde_add_library( index SHARED
  SOURCES
    bitstream.cpp compressed.cpp create.cpp exception.cpp ifile.cpp
    leafdata.cpp leafdatavector.cpp lockfile.cpp logfile.cpp match.cpp
    mmap_manager.cpp quotes.cpp slow.cpp stringarray.cpp stringset.cpp
    tokenizer.cpp
  VERSION 0.0.0
  LINK z
  DESTINATION ${LIB_INSTALL_DIR}
)


##### install import cmake modules ###############

kde_install_export( )
