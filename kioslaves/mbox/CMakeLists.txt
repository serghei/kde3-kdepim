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
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

install( FILES mbox.protocol DESTINATION ${SERVICES_INSTALL_DIR} )


##### kio_mbox (module) #########################

kde_add_kpart( kio_mbox
  SOURCES
    mbox.cc mboxfile.cc readmbox.cc stat.cc urlinfo.cc
  LINK kio-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)
