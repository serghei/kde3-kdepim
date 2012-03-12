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

kde_import( libkmime )

include_directories(
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/libemailfunctions
  ${CMAKE_SOURCE_DIR}/libkmime
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

install( FILES
    imap4.protocol imaps.protocol
  DESTINATION ${SERVICES_INSTALL_DIR} )


##### kio_imap4 (module) ########################

kde_add_kpart( kio_imap4
  SOURCES
    imapcommand.cc imaplist.cc mailaddress.cc mimeheader.cc
    rfcdecoder.cc imap4.cc imapinfo.cc imapparser.cc
    mailheader.cc mimehdrline.cc  mimeio.cc
  LINK emailfunctions-static kmime-shared kio-shared ${SASL_LIBRARY}
  DESTINATION ${PLUGIN_INSTALL_DIR}
)
