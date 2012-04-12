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

add_subdirectory( interfaces )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/libkdenetwork
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
  ${GPGME_INCLUDE_DIRS}
)


##### headers ###################################

install( FILES
    context.h key.h trustitem.h eventloopinteractor.h
    data.h gpgmefw.h result.h keylistresult.h
    keygenerationresult.h importresult.h decryptionresult.h
    verificationresult.h signingresult.h encryptionresult.h
    engineinfo.h
  DESTINATION ${INCLUDE_INSTALL_DIR}/gpgme++ )


##### gpgme++ (shared) ##########################

kde_add_library( gpgme++ SHARED
  SOURCES
    context.cpp key.cpp trustitem.cpp data.cpp
    callbacks.cpp eventloopinteractor.cpp
    keylistresult.cpp keygenerationresult.cpp
    importresult.cpp decryptionresult.cpp
    verificationresult.cpp signingresult.cpp
    encryptionresult.cpp engineinfo.cpp
  VERSION 0.4.0
  LINK ${QT_LIBRARY} ${GPGME_LIBRARIES} ${GPG_ERROR_LIBRARY}
  DESTINATION ${LIB_INSTALL_DIR}
)
