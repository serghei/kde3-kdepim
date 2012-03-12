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

kde_install_icons(
    message_reply mail_get_all
  DESTINATION ${DATA_INSTALL_DIR}/knode/icons )

install( FILES
    stat_edit.png mail.png stat_saved.png ctlart.png greyball.png
    ignore.png newsubs.png stat_sent.png eyes.png greyballchk.png
    snderr.png group.png posting.png stat_cncl.png pgp-keys.png
    group_big.png article.png
  DESTINATION ${DATA_INSTALL_DIR}/knode/pics )
