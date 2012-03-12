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
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### rsslocal (static) #########################

kde_add_library( rsslocal STATIC_PIC AUTOMOC
  SOURCES
    article.cpp document.cpp image.cpp textinput.cpp
    tools_p.cpp loader.cpp enclosure.cpp category.cpp
    feeddetector.cpp
)
