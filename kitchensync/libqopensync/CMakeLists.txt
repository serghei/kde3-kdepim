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

include( ConfigureChecks.cmake )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/..
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
  ${OSENGINE_INCLUDE_DIRS}
  ${OPENSYNC_INCLUDE_DIRS}
)


##### qopensync (shared) ########################

kde_add_library( qopensync SHARED AUTOMOC
  SOURCES
    callbackhandler.cpp conversion.cpp engine.cpp environment.cpp
    filter.cpp group.cpp member.cpp plugin.cpp result.cpp syncmapping.cpp
    syncupdates.cpp syncchange.cpp
  VERSION 0.0.0
  LINK kdeui-shared ${OSENGINE_LIBRARIES} ${OPENSYNC_LIBRARIES}
  DESTINATION ${LIB_INSTALL_DIR}
)
