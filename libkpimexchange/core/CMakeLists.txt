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

kde_import( libkmime )
kde_import( ktnef )
kde_import( libkcal )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### headers ###################################

install( FILES
    exchangeclient.h exchangeaccount.h
  DESTINATION ${INCLUDE_INSTALL_DIR}/kdepim )


##### kpimexchange (shared) #####################

kde_add_library( kpimexchange SHARED AUTOMOC
  SOURCES
    exchangeclient.cpp exchangeaccount.cpp exchangedownload.cpp exchangeupload.cpp
    exchangedelete.cpp utils.cpp exchangeprogress.cpp exchangemonitor.cpp
  VERSION 1.0.0
  LINK ${TQT_LIBRARIES} kcal-shared
  DESTINATION ${LIB_INSTALL_DIR}
)
