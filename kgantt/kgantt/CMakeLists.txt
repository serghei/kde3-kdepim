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


##### headers ###################################

install( FILES
    KGantt.h KGanttItem.h KGanttRelation.h xQGanttBarView.h xQGanttBarViewPort.h
    xQGanttListView.h xQGanttListViewPort.h KGanttBarConfig.h
  DESTINATION ${INCLUDE_INSTALL_DIR}/kgantt )


##### kgantt (shared) ###########################

kde_add_library( kgantt SHARED AUTOMOC
  SOURCES
    KGantt.cpp xQGanttBarViewPort.cpp xQGanttListViewPort.cpp KGanttItem.cpp
    KGanttRelation.cpp xQGanttBarViewPort_Events.cpp xQGanttBarView.cpp
    xQGanttListView.cpp KGanttBarConfig.cpp
  VERSION 0.0.2
  LINK kdeui-shared
  DESTINATION ${LIB_INSTALL_DIR}
)
