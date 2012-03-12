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
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### kdgantt (static) ##########################

kde_add_library( kdgantt STATIC_PIC AUTOMOC
  SOURCES
    KDGanttView.cpp KDGanttViewEventItem.cpp KDGanttViewItem.cpp
    KDGanttViewItemDrag.cpp KDGanttViewSubwidgets.cpp KDGanttViewSummaryItem.cpp
    KDGanttViewTaskItem.cpp KDGanttViewTaskLink.cpp KDGanttViewTaskLinkGroup.cpp
    KDGanttMinimizeSplitter.cpp KDGanttSemiSizingControl.cpp
    KDGanttSizingControl.cpp KDGanttXMLTools.cpp itemAttributeDialog.ui
)
