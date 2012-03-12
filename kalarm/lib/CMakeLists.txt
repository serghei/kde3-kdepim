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
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/kalarm
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### kalarm (static) ###########################

kde_add_library( kalarm STATIC_PIC AUTOMOC
  SOURCES
    buttongroup.cpp checkbox.cpp colourcombo.cpp colourlist.cpp
    combobox.cpp dateedit.cpp datetime.cpp label.cpp
    messagebox.cpp lineedit.cpp synchtimer.cpp pushbutton.cpp
    radiobutton.cpp timeedit.cpp timespinbox.cpp timeperiod.cpp
    shellprocess.cpp slider.cpp spinbox.cpp spinbox2.cpp
)
