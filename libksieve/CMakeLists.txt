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

project( libksieve )

add_subdirectory( ksieve )
add_subdirectory( shared )
add_subdirectory( parser )

include_directories(
  ${QT_INCLUDE_DIR}
)


##### ksieve (shared) ###########################

configure_file( ${TEMPLATE_DUMMY_CPP} dummy.cpp COPYONLY )

kde_add_library( ksieve SHARED
  SOURCES dummy.cpp
  VERSION 0.0.0
  EMBED ksieve_parser-static ksieve_shared-static
  LINK kdecore-shared
  DESTINATION ${LIB_INSTALL_DIR}
)

kde_install_export( )
