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

# FIXME KDE_CXXFLAGS = $(USE_THREADS)

kde_import( ktnef )
kde_import( libkcal )
kde_import( libkmime )
kde_import( libkdepim )
kde_import( libkpgp )

add_subdirectory( pics )
add_subdirectory( filters )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libemailfunctions
  ${CMAKE_SOURCE_DIR}/libkmime
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${CMAKE_SOURCE_DIR}/libkpgp
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

kde_install_icons( )

install( FILES
    KNode.desktop
  DESTINATION ${XDG_APPS_INSTALL_DIR} )

install( FILES
    knewsservice.protocol knode_config_identity.desktop
    knode_config_accounts.desktop knode_config_appearance.desktop
    knode_config_read_news.desktop knode_config_post_news.desktop
    knode_config_privacy.desktop knode_config_cleanup.desktop
  DESTINATION ${SERVICES_INSTALL_DIR} )

install( FILES
    headers.rc knodeui.rc knreaderui.rc kncomposerui.rc
  DESTINATION ${DATA_INSTALL_DIR}/knode )


##### knodecommon (shared) ######################

kde_add_library( knodecommon SHARED AUTOMOC
  SOURCES
    knconfigmanager.cpp knconfig.cpp knconfigwidgets.cpp
    knnetaccess.cpp knprotocolclient.cpp knnntpclient.cpp knjobdata.cpp
    knaccountmanager.cpp kncollection.cpp kncollectionviewitem.cpp
    knserverinfo.cpp knnntpaccount.cpp kngroupmanager.cpp
    knarticlecollection.cpp kngroup.cpp kngroupbrowser.cpp
    kngroupselectdialog.cpp kngroupdialog.cpp kngrouppropdlg.cpp
    knfoldermanager.cpp knfolder.cpp knmemorymanager.cpp
    kncleanup.cpp knconvert.cpp knarticlemanager.cpp knarticle.cpp
    kndisplayedheader.cpp knsourceviewwindow.cpp knarticlewindow.cpp
    knhdrviewitem.cpp kncomposer.cpp knarticlefactory.cpp
    knfiltermanager.cpp knstatusfilter.cpp knstringfilter.cpp
    knrangefilter.cpp knarticlefilter.cpp knfilterconfigwidget.cpp
    knfilterdialog.cpp knsearchdialog.cpp utilities.cpp knscoring.cpp
    knwidgets.cpp headerview.cpp knmainwidget.cpp aboutdata.cpp
    knglobals.cpp knodecomposeriface.skel knodeiface.skel
    kncollectionview.cpp articlewidget.cpp csshelper.cpp
    smtpaccountwidget_base.ui
  VERSION 3.0.0
  LINK emailfunctions-static kdepim-shared kpgp-shared khtml-shared
  DESTINATION ${LIB_INSTALL_DIR}
)


##### kcm_knode (module) ########################

kde_add_kpart( kcm_knode AUTOMOC
  SOURCES
    knconfigpages.cpp
  LINK knodecommon-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### libknodepart (module) #####################

kde_add_kpart( libknodepart AUTOMOC
  SOURCES
    knode_part.cpp
  LINK knodecommon-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### knode (executable) ########################

kde_add_executable( knode AUTOMOC
  SOURCES
    knode.cpp knapplication.cpp main.cpp
  LINK knodecommon-shared
  DESTINATION ${BIN_INSTALL_DIR}
)
