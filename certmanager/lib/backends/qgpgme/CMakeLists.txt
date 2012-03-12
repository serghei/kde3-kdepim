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

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/certmanager/lib
  ${CMAKE_SOURCE_DIR}/libkdenetwork
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
  ${GPGME_INCLUDE_DIRS}
)


##### kleopatra_backend_qgpgme (static) #########

kde_add_library( kleopatra_backend_qgpgme STATIC_PIC AUTOMOC
  SOURCES
    gnupgprocessbase.cpp qgpgmeprogresstokenmapper.cpp
    qgpgmebackend.cpp qgpgmejob.cpp qgpgmekeylistjob.cpp
    qgpgmekeygenerationjob.cpp qgpgmeimportjob.cpp
    qgpgmeexportjob.cpp qgpgmesecretkeyexportjob.cpp
    qgpgmedownloadjob.cpp qgpgmedeletejob.cpp
    qgpgmeencryptjob.cpp qgpgmedecryptjob.cpp
    qgpgmesignjob.cpp qgpgmeverifydetachedjob.cpp
    qgpgmeverifyopaquejob.cpp qgpgmesignencryptjob.cpp
    qgpgmedecryptverifyjob.cpp qgpgmecryptoconfig.cpp
    qgpgmerefreshkeysjob.cpp
)
