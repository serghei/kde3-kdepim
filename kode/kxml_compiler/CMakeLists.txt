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
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### kxml_compiler (executable) ################

kde_add_executable( kxml_compiler
  SOURCES
    parser.cpp creator.cpp kxml_compiler.cpp
  LINK kode-shared
  DESTINATION ${BIN_INSTALL_DIR}
)
