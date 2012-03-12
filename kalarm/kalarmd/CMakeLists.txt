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
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

install( FILES kalarmd.autostart.desktop DESTINATION ${AUTOSTART_INSTALL_DIR} )
install( FILES kalarmd.desktop DESTINATION ${APPS_INSTALL_DIR}/.hidden )


##### kalarmd (executable) ######################

kde_add_executable( kalarmd AUTOMOC
  SOURCES
    adcalendar.cpp adconfigdata.cpp clientinfo.cpp
    alarmdaemon.cpp admain.cpp adapp.cpp alarmdaemoniface.skel
  LINK kalarmd-static kcal-shared
  DESTINATION ${BIN_INSTALL_DIR}
)


##### kalarmd (static) ##########################

kde_add_library( kalarmd STATIC_PIC
  SOURCES alarmdaemoniface.stub alarmguiiface.stub
)
