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
  ${QT_INCLUDE_DIR}
)


##### other data ################################

install( FILES
    korn-3-4-config_change.upd korn-3-5-update.upd
  DESTINATION ${KCONF_UPDATE_INSTALL_DIR} )

install( PROGRAMS
    korn-3-5-ssl-update.pl korn-3-5-metadata-update.pl
  DESTINATION ${KCONF_UPDATE_INSTALL_DIR} )


##### korn-3-4-config_change (executable) #######

kde_add_executable( korn-3-4-config_change
  SOURCES korn-3-4-config_change.cpp
  LINK ${QT_LIBRARY}
  DESTINATION ${LIB_INSTALL_DIR}/kconf_update_bin
)
