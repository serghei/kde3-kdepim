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
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### kabc2mutt (executable) ####################

kde_add_executable( kabc2mutt AUTOMOC
  SOURCES kabc2mutt.cpp main.cpp
  LINK kabc-shared
  DESTINATION ${BIN_INSTALL_DIR}
)
