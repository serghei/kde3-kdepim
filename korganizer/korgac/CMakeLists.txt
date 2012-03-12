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

add_subdirectory( pixmaps )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/korganizer
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

install( FILES korgac.desktop DESTINATION ${AUTOSTART_INSTALL_DIR} )


##### korgac (executable) #######################

kde_add_executable( korgac AUTOMOC
  SOURCES
    korgacmain.cpp alarmdialog.cpp alarmdockwindow.cpp koalarmclient.cpp
    alarmclientiface.skel
  LINK korganizer_eventviewer-shared
  DESTINATION ${BIN_INSTALL_DIR}
)
