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

kde_install_icons( gpg gpgsm )

install( FILES
    key.png key_ok.png key_bad.png key_unknown.png chiasmus_chi.png
  DESTINATION ${DATA_INSTALL_DIR}/libkleopatra/pics )
