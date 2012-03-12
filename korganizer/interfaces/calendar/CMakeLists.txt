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

install( FILES
    plugin.h calendardecoration.h
  DESTINATION ${INCLUDE_INSTALL_DIR}/calendar )

install( FILES
    calendarplugin.desktop calendardecoration.desktop
  DESTINATION ${SERVICETYPES_INSTALL_DIR} )
