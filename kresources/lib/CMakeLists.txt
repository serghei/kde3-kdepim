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
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### kgroupwarebase (shared) ###################

kde_add_library( kgroupwarebase SHARED AUTOMOC
  SOURCES
    folderlister.cpp folderconfig.cpp folderlistview.cpp folderselectdialog.cpp
    groupwaredataadaptor.cpp groupwaredownloadjob.cpp calendaradaptor.cpp
    addressbookadaptor.cpp groupwareresourcejob.cpp groupwareuploadjob.cpp
    kcal_resourcegroupwarebase.cpp kabc_resourcegroupwarebase.cpp
    kresources_groupwareprefs.kcfgc kcal_resourcegroupwarebaseconfig.cpp
    kabc_resourcegroupwarebaseconfig.cpp kcal_cachesettingsdlg.cpp
  VERSION 0.0.0
  LINK kdepim-shared
  DESTINATION ${LIB_INSTALL_DIR}
)


##### kgroupwaredav (shared) ####################

kde_add_library( kgroupwaredav SHARED AUTOMOC
  SOURCES
    davcalendaradaptor.cpp davaddressbookadaptor.cpp webdavhandler.cpp
    davgroupwareglobals.cpp
  VERSION 0.0.0
  LINK kgroupwarebase-shared
  DESTINATION ${LIB_INSTALL_DIR}
)
