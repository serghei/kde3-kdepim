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

if( BUILD_KODE )
  set( KXML_COMPILER_EXECUTABLE ${CMAKE_BINARY_DIR}/kode/kxml_compiler/kxml_compiler )
  set( KXML_COMPILER_TARGET kxml_compiler )
else( )
  find_program( KXML_COMPILER_EXECUTABLE
    NAMES kxml_compiler
    HINTS ${TDE_BIN_DIR} ${BIN_INSTALL_DIR} )
  if( NOT KXML_COMPILER_EXECUTABLE )
    kde_message_fatal( "kxml_compiler is NOT found.\n kode package is correctly installed?" )
  endif( )
endif( )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

install( FILES
    kcal_resourcefeatureplan.desktop
  DESTINATION ${SERVICES_INSTALL_DIR}/kresources/kcal )


##### kcal_resourcefeatureplan (module) #########

kde_add_kpart( kcal_resourcefeatureplan AUTOMOC
  SOURCES kcal_resourcefeatureplanplugin.cpp
  LINK kcal_resourcefeatureplan-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### featureplancommon (static) ################

add_custom_command(
  OUTPUT kde-features.h kde-features.cpp kde-features_parser.h kde-features_parser.cpp
  COMMAND ${KXML_COMPILER_EXECUTABLE} --custom-parser ${CMAKE_CURRENT_SOURCE_DIR}/kde-features.rng >/dev/null
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/kde-features.rng ${KXML_COMPILER_TARGET} )

kde_add_library( featureplancommon STATIC_PIC
  SOURCES
    kde-features.cpp kde-features_parser.cpp prefs.kcfgc
)


##### kcal_resourcefeatureplan (shared) #########

kde_add_library( kcal_resourcefeatureplan SHARED AUTOMOC
  SOURCES
    kcal_resourcefeatureplan.cpp kcal_resourcefeatureplanconfig.cpp
  VERSION 1.0.0
  LINK featureplancommon-static kdepim-shared
  DESTINATION ${LIB_INSTALL_DIR}
)
