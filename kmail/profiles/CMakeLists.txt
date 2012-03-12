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

set( profiles default html high-contrast purist secure )

foreach( profile ${profiles} )
  install( FILES "profile-${profile}-rc.desktop"
    DESTINATION ${DATA_INSTALL_DIR}/kmail
    RENAME profile-${profile}-rc )
endforeach( )
