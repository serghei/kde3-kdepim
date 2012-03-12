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
  ${CMAKE_SOURCE_DIR}/kaddressbook
  ${CMAKE_SOURCE_DIR}/kaddressbook/interfaces
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


if( WITH_NEWDISTRLISTS )
  set( DESKTOP distributionlistng.desktop )
  set( SOURCE distributionlistngwidget.cpp )
  set( TARGET libkaddrbk_distributionlistng )
else( )
  set( DESKTOP distributionlist.desktop )
  set( SOURCE distributionlistwidget.cpp )
  set( TARGET libkaddrbk_distributionlist )
endif( )


##### other data ################################

install( FILES
    ${DESKTOP} resourceselection.desktop
  DESTINATION ${SERVICES_INSTALL_DIR}/kaddressbook )


##### libkaddrbk_distributionlist (module) ######

kde_add_kpart( ${TARGET} AUTOMOC
  SOURCES ${SOURCE}
  LINK kabinterfaces-shared kdepim-shared kabc-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### libkaddrbk_resourceselection (module) #####

kde_add_kpart( libkaddrbk_resourceselection AUTOMOC
  SOURCES resourceselection.cpp
  LINK kabinterfaces-shared kdepim-shared kabc-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)
