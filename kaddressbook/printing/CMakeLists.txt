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
  ${CMAKE_BINARY_DIR}/kaddressbook/common
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/kaddressbook
  ${CMAKE_SOURCE_DIR}/kaddressbook/common
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### printer (static) ##########################

kde_add_library( printer STATIC_PIC AUTOMOC
  SOURCES
    detailledstyle.cpp ds_appearance.ui kabentrypainter.cpp mikesstyle.cpp
    printingwizard.cpp printprogress.cpp printstyle.cpp selectionpage.cpp
    stylepage.cpp printsortmode.cpp
)
