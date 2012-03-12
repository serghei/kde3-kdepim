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

install( FILES sieve.protocol DESTINATION ${SERVICES_INSTALL_DIR} )


##### kio_sieve (module) ########################

kde_add_kpart( kio_sieve
  SOURCES sieve.cpp
  LINK kio-shared ${SASL_LIBRARY}
  DESTINATION ${PLUGIN_INSTALL_DIR}
)
