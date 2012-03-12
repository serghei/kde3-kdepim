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
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

install( FILES ldifvcardthumbnail.desktop DESTINATION ${SERVICES_INSTALL_DIR} )


##### ldifvcardthumbnail (module) ###############

kde_add_kpart( ldifvcardthumbnail
  SOURCES ldifvcardcreator.cpp
  LINK kabc-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)
