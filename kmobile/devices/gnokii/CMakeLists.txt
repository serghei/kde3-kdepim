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
  ${CMAKE_CURRENT_SOURCE_DIR}/../..
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
  ${GNOKII_INCLUDE_DIRS}
)


##### other data ################################

install( FILES
    libkmobile_gnokii.desktop
  DESTINATION ${SERVICES_INSTALL_DIR} )


##### libkmobile_gnokii (module) ################

kde_add_kpart( libkmobile_gnokii AUTOMOC
  SOURCES
    gnokii_mobile.cpp gnokiiconfigui.ui gnokiiconfig.cpp
  LINK kmobiledevice-shared kcal-shared ${GNOKII_LIBRARIES}
  DESTINATION ${PLUGIN_INSTALL_DIR}
)
