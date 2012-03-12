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
  ${CMAKE_BINARY_DIR}
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

install( FILES kfile_vcf.desktop DESTINATION ${SERVICES_INSTALL_DIR} )


##### kfile_vcf (module) ########################

kde_add_kpart( kfile_vcf AUTOMOC
  SOURCES kfile_vcf.cpp
  LINK kabc-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)
