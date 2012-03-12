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

# FIXME need some configure checks

project( libkmime )

include( ConfigureChecks.cmake )

include_directories(
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### kmime (shared) ############################

kde_add_library( kmime SHARED
  SOURCES
    kmime_charfreq.cpp kmime_util.cpp kmime_mdn.cpp
    kmime_codecs.cpp kmime_codec_base64.cpp kmime_codec_uuencode.cpp
    kmime_codec_qp.cpp kmime_codec_identity.cpp kmime_parsers.cpp
    kmime_header_parsing.cpp kmime_content.cpp kmime_headers.cpp
    kmime_message.cpp kmime_newsarticle.cpp boolflags.cpp
    kqcstringsplitter.cpp
  VERSION 2.2.0
  LINK kdecore-shared
  DESTINATION ${LIB_INSTALL_DIR}
)


##### install import cmake modules ###############

kde_install_export( )
