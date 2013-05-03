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

project( kmail )

if( WITH_INDEXLIB )
  kde_import( indexlib )
  add_definitions( -DHAVE_INDEXLIB )
  set( INDEX_LIBRARY index-shared )
endif( )

kde_import( libkdenetwork )
kde_import( certmanager )
kde_import( ktnef )
kde_import( libkcal )
kde_import( libkmime )
kde_import( libkpgp )
kde_import( libkdepim )
kde_import( mimelib )
kde_import( libkpimidentities )
kde_import( libksieve )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions" )

add_subdirectory( interfaces )
add_subdirectory( about )
add_subdirectory( pics )
add_subdirectory( profiles )
add_subdirectory( avscripts )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libemailfunctions
  ${CMAKE_SOURCE_DIR}/mimelib
  ${CMAKE_SOURCE_DIR}/libkmime
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${CMAKE_SOURCE_DIR}/libkpgp
  ${CMAKE_SOURCE_DIR}/libkdenetwork
  ${CMAKE_SOURCE_DIR}/certmanager/lib
  ${CMAKE_SOURCE_DIR}/libksieve
  ${CMAKE_SOURCE_DIR}/ktnef
  ${CMAKE_SOURCE_DIR}/korganizer
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
  ${GPGME_INCLUDE_DIRS}
)

link_directories(
  ${QT_LIBRARY_DIR}
)


##### headers ###################################

install( FILES
    kmailIface.h kmailpartIface.h kmailicalIface.h
  DESTINATION ${INCLUDE_INSTALL_DIR} )


##### other data ################################

kde_install_icons( )

install( FILES
    KMail.desktop kmail_view.desktop
  DESTINATION ${XDG_APPS_INSTALL_DIR} )

install( FILES
    kmcomposerui.rc kmmainwin.rc kmreadermainwin.rc
    eventsrc kmail_part.rc
  DESTINATION ${DATA_INSTALL_DIR}/kmail )

install( FILES
    kmail.upd
  DESTINATION ${KCONF_UPDATE_INSTALL_DIR} )

install( PROGRAMS
    upgrade-transport.pl kmail-pgpidentity.pl
    upgrade-signature.pl kmail-upd-identities.pl
    kmail-3.1-use-UOID-for-identities.pl
    kmail-3.1-update-new-mail-notification-settings.pl
    kmail-3.1.4-dont-use-UOID-0-for-any-identity.pl
    kmail-3.2-update-loop-on-goto-unread-settings.sh
    kmail-3.2-misc.sh kmail-3.3-use-ID-for-accounts.pl
    kmail-3.3-move-identities.pl kmail-3.3-aegypten.pl
    kmail-3.3-split-sign-encr-keys.sh kmail-3.3-misc.pl
    kmail-3.3b1-misc.pl kmail-3.4-misc.pl
    kmail-3.4.1-update-status-filters.pl
    kmail-3.5-trigger-flag-migration.pl
  DESTINATION ${KCONF_UPDATE_INSTALL_DIR} )

install( FILES
    kmail.antispamrc kmail.antivirusrc
  DESTINATION ${CONFIG_INSTALL_DIR} )

install( FILES
    tips
  DESTINATION ${DATA_INSTALL_DIR}/kmail )

install( FILES
    dcopmail.desktop dcopimap.desktop
  DESTINATION ${SERVICETYPES_INSTALL_DIR} )

install( FILES
    kmail_config_misc.desktop kmail_config_appearance.desktop
    kmail_config_identity.desktop kmail_config_accounts.desktop
    kmail_config_composer.desktop kmail_config_security.desktop
  DESTINATION ${SERVICES_INSTALL_DIR} )

install( FILES
    kmail.kcfg replyphrases.kcfg custommimeheader.kcfg
    templatesconfiguration_kfg.kcfg customtemplates_kfg.kcfg
  DESTINATION ${KCFG_INSTALL_DIR} )

install( FILES
    application_octetstream.desktop
  DESTINATION ${DATA_INSTALL_DIR}/kmail/plugins/bodypartformatter )


##### kmailprivate (shared) #####################

set( target kmailprivate )

set( ${target}_SRCS
  kmmessage.cpp kmmainwin.cpp configuredialog.cpp configuredialog_p.cpp
  klistviewindexedsearchline.cpp simplestringlisteditor.cpp index.cpp headeritem.cpp
  identitydrag.cpp identitylistview.cpp identitydialog.cpp kmfolderdia.cpp kmmsgdict.cpp
  kmfoldertree.cpp kmtransport.cpp kmfoldercombobox.cpp kmaccount.cpp kmheaders.cpp
  kmcomposewin.cpp kmfolder.cpp kmmsgpartdlg.cpp kmreaderwin.cpp htmlstatusbar.cpp
  kmgroupware.cpp folderstorage.cpp listjob.cpp csshelper.cpp klistboxdialog.cpp
  kmmsginfo.cpp actionscheduler.cpp messageproperty.cpp accountmanager.cpp kmacctfolder.cpp
  kmdict.cpp kmsystemtray.cpp kmacctlocal.cpp kmfolderdir.cpp kmfoldermgr.cpp
  kmfoldernode.cpp kmsender.cpp kmacctseldlg.cpp kmfiltermgr.cpp kmfilterdlg.cpp
  filterimporterexporter.cpp kmsearchpatternedit.cpp encodingdetector.cpp encodingdetector_ja.cpp
  kmfilteraction.cpp kmsearchpattern.cpp kmfolderimap.cpp kmfolderseldlg.cpp kmfilter.cpp
  kmmsgpart.cpp kmmsgbase.cpp kmmsglist.cpp kmaddrbook.cpp signatureconfigurator.cpp
  xfaceconfigurator.cpp networkaccount.cpp imapaccountbase.cpp popaccount.cpp kmservertest.cpp
  kmacctimap.cpp kmacctcachedimap.cpp kmfawidgets.cpp kmfoldermbox.cpp colorlistbox.cpp
  undostack.cpp kmfoldercachedimap.cpp attachmentstrategy.cpp kmfoldermaildir.cpp
  kmkernel.cpp accountdialog.cpp searchwindow.cpp vcardviewer.cpp vacationdialog.cpp
  vacation.cpp sievedebugdialog.cpp sieveconfig.cpp sievejob.cpp kmpopheaders.cpp
  kmpopfiltercnfrmdlg.cpp kmmimeparttree.cpp mailinglist-magic.cpp kmacctmaildir.cpp
  headerstyle.cpp headerstrategy.cpp khtmlparthtmlwriter.cpp filehtmlwriter.cpp
  teehtmlwriter.cpp mailcomposerIface.skel objecttreeparser.cpp
  attachmentcollector.cpp bodypartformatterfactory.cpp bodypartformatter.cpp partNode.cpp
  mailsourceviewer.cpp kmcommands.cpp kmreadermainwin.cpp kmstartup.cpp kmmainwidget.cpp
  folderpropertiesdialog.ui kmfolderindex.cpp kmfoldersearch.cpp transportmanager.cpp
  imapjob.cpp folderjob.cpp cachedimapjob.cpp maildirjob.cpp mboxjob.cpp subscriptiondialog.cpp
  kmailicalifaceimpl.cpp aboutdata.cpp folderIface.cpp folderIface.skel mailserviceimpl.cpp
  attachmentlistview.cpp kmedit.cpp kmlineeditspell.cpp kmatmlistview.cpp composer.cpp
  isubject.cpp bodyvisitor.cpp antispamwizard.cpp urlhandlermanager.cpp dictionarycombobox.cpp
  secondarywindow.cpp filterlog.cpp filterlogdlg.cpp messagecomposer.cpp keyresolver.cpp
  globalsettings.cpp globalsettings_base.kcfgc regexplineedit.cpp rulewidgethandlermanager.cpp
  headerlistquicksearch.cpp acljobs.cpp folderdiaacltab.cpp quotajobs.cpp expirejob.cpp
  folderdiaquotatab.cpp folderdiaquotatab_p.cpp jobscheduler.cpp partnodebodypart.cpp
  compactionjob.cpp callback.cpp searchjob.cpp renamejob.cpp composercryptoconfiguration.ui
  warningconfiguration.ui smimeconfiguration.ui annotationjobs.cpp accountcombobox.cpp
  redirectdialog.cpp foldershortcutdialog.cpp folderrequester.cpp spamheaderanalyzer.cpp
  antispamconfig.cpp replyphrases.kcfgc custommimeheader.kcfgc recipientseditor.cpp
  recipientspicker.cpp kwindowpositioner.cpp textsource.cpp distributionlistdialog.cpp
  expirypropertiesdialog.cpp scalix.cpp mailinglistpropertiesdialog.cpp newfolderdialog.cpp
  accountwizard.cpp managesievescriptsdialog.cpp chiasmuskeyselector.cpp
  util.cpp templatesinsertcommand.cpp customtemplates_base.ui customtemplates.cpp
  customtemplates_kfg.kcfgc templatesconfiguration_base.ui templatesconfiguration.cpp
  templatesconfiguration_kfg.kcfgc templateparser.cpp copyfolderjob.cpp messagecopyhelper.cpp
  localsubscriptiondialog.cpp editorwatcher.cpp favoritefolderview.cpp
  foldertreebase.cpp snippetdlgbase.ui snippetwidget.cpp snippetconfig.cpp
  snippetdlg.cpp snippetitem.cpp snippetsettings.cpp snippetsettingsbase.ui
  messageactions.cpp korghelper.cpp kmnetworkmonitor.cpp
  ${CMAKE_SOURCE_DIR}/korganizer/kcalendariface.stub
  kmailIface.skel_ng kmailicalIface.skel_ng
  ${CMAKE_SOURCE_DIR}/korganizer/korganizeriface.stub )

kde_add_library( ${target} SHARED AUTOMOC
  SOURCES ${${target}_SRCS}
  LINK
    emailfunctions-static kmime-shared kpgp-shared kdepim-shared kpimidentities-shared
    mimelib-shared ksieve-shared khtml-shared kdedbus-shared ${INDEX_LIBRARY}
  DESTINATION ${LIB_INSTALL_DIR}
)


##### kmail (executable) ########################

kde_add_executable( kmail
  SOURCES main.cpp
  LINK kmailprivate-shared
  DESTINATION ${BIN_INSTALL_DIR}
)


##### kcm_kmail (module) ########################

kde_add_kpart( kcm_kmail AUTOMOC
  SOURCES kcm_kmail.cpp
  LINK kmailprivate-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### libkmailpart (module) #####################

kde_add_kpart( libkmailpart AUTOMOC
  SOURCES kmailpartIface.skel kmail_part.cpp
  LINK kmailprivate-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### libkmail_bodypartformatter_application_octetstream (module)

kde_add_kpart( libkmail_bodypartformatter_application_octetstream
  SOURCES app_octetstream.cpp
  LINK ${QT_LIBRARIES}
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### install import cmake modules ###############

kde_install_export( )
