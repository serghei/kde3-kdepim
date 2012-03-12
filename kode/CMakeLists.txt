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

add_subdirectory( kxml_compiler )

include_directories(
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### kode (executable) #########################

kde_add_executable( kode
  SOURCES kodemain.cpp
  LINK kode-shared kabc-shared
  DESTINATION ${BIN_INSTALL_DIR}
)


##### kode (shared) #############################

kde_add_library( kode SHARED
  SOURCES
    code.cpp enum.cpp style.cpp printer.cpp license.cpp file.cpp class.cpp
    function.cpp variable.cpp membervariable.cpp typedef.cpp statemachine.cpp
    automakefile.cpp
  VERSION 1.0.0
  LINK kdecore-shared
  DESTINATION ${LIB_INSTALL_DIR}
)
