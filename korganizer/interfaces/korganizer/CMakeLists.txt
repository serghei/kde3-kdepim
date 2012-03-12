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
    part.h baseview.h calendarviewbase.h mainwindow.h corehelper.h printplugin.h
  DESTINATION ${INCLUDE_INSTALL_DIR}/korganizer )

install( FILES
    korganizerpart.desktop korgprintplugin.desktop
  DESTINATION ${SERVICETYPES_INSTALL_DIR} )
