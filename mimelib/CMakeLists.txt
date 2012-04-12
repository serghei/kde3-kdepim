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

project( mimelib )

add_subdirectory( mimelib )

add_definitions(
  -DDW_DEVELOPMENT_VERSION
  -D_REENTRANT
)

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### mimelib (shared) ##########################

kde_add_library( mimelib SHARED
  SOURCES
    protocol.cpp address.cpp addrlist.cpp body.cpp
    bodypart.cpp boyermor.cpp datetime.cpp disptype.cpp
    dw_cte.cpp dw_date.cpp dw_mime.cpp entity.cpp
    field.cpp fieldbdy.cpp group.cpp headers.cpp mailbox.cpp
    mboxlist.cpp mechansm.cpp mediatyp.cpp message.cpp
    msgcmp.cpp msgid.cpp nntp.cpp param.cpp pop.cpp
    dwstring.cpp text.cpp token.cpp uuencode.cpp
    binhex.cpp
  VERSION 1.0.1
  LINK ${KDE_LIBRARY_DIR}/libkdefakes_pic.a
  DESTINATION ${LIB_INSTALL_DIR}
)

kde_install_export( )
