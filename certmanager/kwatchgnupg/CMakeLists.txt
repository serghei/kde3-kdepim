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

add_definitions( -DLIBKLEOPATRA_NO_COMPAT )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/certmanager/lib
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

install( FILES
    kwatchgnupg.png kwatchgnupg2.png
  DESTINATION ${DATA_INSTALL_DIR}/kwatchgnupg/pics )

install( FILES
    kwatchgnupgui.rc
  DESTINATION ${DATA_INSTALL_DIR}/kwatchgnupg )


##### kwatchgnupg (executable) ##################

kde_add_executable( kwatchgnupg AUTOMOC
  SOURCES
    kwatchgnupgmainwin.cpp kwatchgnupgconfig.cpp
    aboutdata.cpp tray.cpp main.cpp
  LINK kleopatra-shared
  DESTINATION ${BIN_INSTALL_DIR}
)
