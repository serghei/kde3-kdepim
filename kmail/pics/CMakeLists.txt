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

add_subdirectory( icons )

install( FILES
    kmmsgdel.png kmmsgnew.png kmmsgunseen.png kmmsgread.png
    kmmsgreplied.png kmmsgforwarded.png kmmsgqueued.png
    kmmsgflag.png kmmsgsent.png kmmsgwatched.png kmmsgignored.png
    kmmsgtodo.png kmmsgread_fwd.png kmmsgread_replied.png
    kmmsgread_fwd_replied.png pgp-keys.png kmmsgpartiallyencrypted.png
    kmmsgpartiallysigned.png kmmsgfullyencrypted.png kmmsgfullysigned.png
    kmmsgundefinedencrypted.png kmmsgundefinedsigned.png kmmsgspam.png
    kmmsgham.png kmmsgattachment.png kmwizard.png
    quotecollapse.png quoteexpand.png enterprise_bottom_left.png
    enterprise_bottom.png enterprise_bottom_right.png enterprise_icon.png
    enterprise_left.png enterprise_right.png enterprise_s_left.png
    enterprise_sbar.png enterprise_s_right.png enterprise_sp_right.png
    enterprise_top_left.png enterprise_top.png enterprise_top_right.png
    enterprise_sw.png enterprise_w.png attachmentQuicklistClosed.png
    attachmentQuicklistOpened.png
  DESTINATION ${DATA_INSTALL_DIR}/kmail/pics )
