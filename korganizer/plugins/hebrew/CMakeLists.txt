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
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/korganizer/interfaces
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

install( FILES hebrew.desktop DESTINATION ${SERVICES_INSTALL_DIR}/korganizer )


##### libkorg_hebrew (module) ###################

kde_add_kpart( libkorg_hebrew AUTOMOC
  SOURCES
    hebrew.cpp configdialog.cpp holiday.cpp parsha.cpp converter.cpp
  LINK kdeui-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)
