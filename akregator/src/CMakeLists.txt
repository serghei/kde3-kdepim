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

kde_import( libkmime)
kde_import( ktnef )
kde_import( libkcal )
kde_import( libkdepim )

add_subdirectory( librss )
add_subdirectory( about )
add_subdirectory( mk4storage )
add_subdirectory( pics )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### headers ###################################

install( FILES
    plugin.h articleinterceptor.h akregator_export.h storage.h
    feedstorage.h storagefactory.h storagefactoryregistry.h
  DESTINATION ${INCLUDE_INSTALL_DIR}/akregator )


##### other data ################################

kde_install_icons( )

install( FILES
    akregator.desktop
  DESTINATION ${XDG_APPS_INSTALL_DIR} )

install( FILES
    akregator.kcfg
  DESTINATION ${KCFG_INSTALL_DIR} )

install( FILES
    akregator_part.desktop feed.protocol
  DESTINATION ${SERVICES_INSTALL_DIR} )

install( FILES
    akregator_plugin.desktop
  DESTINATION ${SERVICETYPES_INSTALL_DIR} )

install( FILES
    akregator_shell.rc articleviewer.rc eventsrc
    pageviewer.rc akregator_part.rc
  DESTINATION ${DATA_INSTALL_DIR}/akregator )


##### akregatorprivate (shared) #################

kde_add_library( akregatorprivate SHARED AUTOMOC
  SOURCES
    aboutdata.cpp akregatorconfig.kcfgc article.cpp
    articlefilter.cpp articleinterceptor.cpp dragobjects.cpp
    feed.cpp feediconmanager.cpp feediconmanager.skel
    feedlist.cpp feedstoragedummyimpl.cpp fetchqueue.cpp
    folder.cpp nodelist.cpp plugin.cpp pluginmanager.cpp
    simplenodeselector.cpp storage.cpp storagedummyimpl.cpp
    storagefactorydummyimpl.cpp storagefactoryregistry.cpp
    tag.cpp tagfolder.cpp tagnode.cpp tagnodelist.cpp
    tagset.cpp trayicon.cpp treenode.cpp treenodevisitor.cpp
    utils.cpp
  VERSION 0.0.0
  LINK rsslocal-static kio-shared
  DESTINATION ${LIB_INSTALL_DIR}
)


##### akregator (executable) ####################

kde_add_executable( akregator AUTOMOC
  SOURCES main.cpp mainwindow.cpp
  LINK akregatorprivate-shared kdepim-shared kparts-shared
  DESTINATION ${BIN_INSTALL_DIR}
)


##### libakregatorpart (module) #################

kde_add_kpart( libakregatorpart AUTOMOC
  SOURCES
    actionmanager.cpp actionmanagerimpl.cpp
    addfeeddialog.cpp addfeedwidgetbase.ui
    akregator_part.cpp akregator_partiface.skel
    akregator_run.cpp akregator_view.cpp articlelistview.cpp
    articleviewer.cpp configdialog.cpp feeditem.cpp
    feedlistview.cpp folderitem.cpp frame.cpp kernel.cpp
    notificationmanager.cpp pageviewer.cpp progressmanager.cpp
    propertiesdialog.cpp propertieswidgetbase.ui searchbar.cpp
    settings_advancedbase.ui settings_advanced.cpp
    settings_appearance.ui settings_archive.ui
    settings_browser.ui settings_general.ui speechclient.cpp
    tabwidget.cpp tagaction.cpp tagfolderitem.cpp
    tagnodeitem.cpp tagpropertiesdialog.cpp
    tagpropertieswidgetbase.ui treenodeitem.cpp
    viewer.cpp ${KDE_INCLUDE_DIR}/kspeechsink.skel
    ${KDE_INCLUDE_DIR}/kspeech.stub listtabwidget.cpp
  LINK akregatorprivate-shared kdepim-shared khtml-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)
