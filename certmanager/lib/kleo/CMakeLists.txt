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
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${CMAKE_SOURCE_DIR}/libkdenetwork
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### headers ###################################

install( FILES
    enum.h cryptobackend.h cryptobackendfactory.h
    cryptoconfig.h dn.h job.h keylistjob.h keygenerationjob.h
    importjob.h exportjob.h downloadjob.h deletejob.h
    encryptjob.h decryptjob.h signjob.h verifydetachedjob.h
    verifyopaquejob.h decryptverifyjob.h signencryptjob.h
    refreshkeysjob.h multideletejob.h hierarchicalkeylistjob.h
    keyfilter.h keyfiltermanager.h
  DESTINATION ${INCLUDE_INSTALL_DIR}/kleo )


##### kleopatra_core (static) ###################

kde_add_library( kleopatra_core STATIC_PIC AUTOMOC
  SOURCES
    cryptobackend.cpp cryptobackendfactory.cpp
    enum.cpp dn.cpp job.cpp multideletejob.cpp
    hierarchicalkeylistjob.cpp kconfigbasedkeyfilter.cpp
    keyfiltermanager.cpp
)
