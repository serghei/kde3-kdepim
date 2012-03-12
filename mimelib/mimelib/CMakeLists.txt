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
    address.h addrlist.h body.h bodypart.h boyermor.h
    config.h datetime.h debug.h disptype.h entity.h
    enum.h field.h fieldbdy.h group.h headers.h mailbox.h
    mboxlist.h mechansm.h mediatyp.h message.h mimepp.h
    msgcmp.h msgid.h nntp.h param.h pop.h protocol.h
    string.h text.h token.h utility.h uuencode.h binhex.h
  DESTINATION ${INCLUDE_INSTALL_DIR}/mimelib )
