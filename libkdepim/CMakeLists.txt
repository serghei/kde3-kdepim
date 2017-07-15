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

project( libkdepim )

include( ConfigureChecks.cmake )

kde_import( libkmime )
kde_import( libkcal )
kde_import( ktnef )

add_subdirectory( icons )
add_subdirectory( pics )
add_subdirectory( kpartsdesignerplugin )
add_subdirectory( about )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)

link_directories(
  ${QT_LIBRARY_DIR}
)


##### headers ###################################

install( FILES
    kdepimmacros.h kpimprefs.h
  DESTINATION ${INCLUDE_INSTALL_DIR} )


##### other data ################################

install( FILES pimemoticons.kcfg DESTINATION ${KCFG_INSTALL_DIR} )


##### kdepimwidgets (module) ####################

add_custom_command( OUTPUT kdepimwidgets.cpp
  COMMAND
    ${KDE_MAKEKDEWIDGETS_EXECUTABLE}
    -o kdepimwidgets.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/kdepim.widgets
  DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/kdepim.widgets )

set_source_files_properties( kdepimwidgets.cpp PROPERTIES COMPILE_FLAGS "-DQT_PLUGIN" )

kde_add_kpart( kdepimwidgets
  SOURCES kdepimwidgets.cpp
  LINK kdepim-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}/plugins/designer
)


##### kdepim (shared) ###########################

kde_add_library( kdepim SHARED AUTOMOC
  SOURCES
    ktimeedit.cpp alarmclient.cpp kprefsdialog.cpp kpimprefs.cpp
    categoryselectdialog_base.ui categoryselectdialog.cpp
    categoryeditdialog_base.ui categoryeditdialog.cpp kdateedit.cpp
    kimportdialog.cpp kvcarddrag.cpp sidebarextension.cpp
    infoextension.cpp addressesdialog.cpp addresspicker.ui
    addresseeview.cpp maillistdrag.cpp interfaces/MailTransportServiceIface.skel_ng
    interfaces/AddressBookServiceIface.skel kconfigpropagator.cpp kconfigwizard.cpp
    weaver.cpp weaverextensions.cpp weaverlogger.cpp pluginloaderbase.cpp
    addresseelineedit.cpp addresseelineedit.skel kdatepickerpopup.cpp
    kfileio.cpp clicklineedit.cpp configmanager.cpp collectingprocess.cpp
    ldapclient.cpp overlaywidget.cpp progressmanager.cpp progressdialog.cpp
    statusbarprogresswidget.cpp ssllabel.cpp completionordereditor.cpp
    resourceabc.cpp diffalgo.cpp addresseediffalgo.cpp calendardiffalgo.cpp
    htmldiffalgodisplay.cpp ldapsearchdialog.cpp broadcaststatus.cpp
    kresourceprefs.cpp kpixmapregionselectorwidget.cpp
    kpixmapregionselectordialog.cpp kabcresourcecached.cpp
    kxface.cpp kaccount.cpp kaddrbook.cpp kfoldertree.cpp kregexp3.cpp
    kscoring.cpp kscoringeditor.cpp ksubscription.cpp kwidgetlister.cpp
    linklocator.cpp qutf7codec.cpp recentaddresses.cpp spellingfilter.cpp
    addresseeselector.cpp addresseeemailselection.cpp designerfields.cpp
    kcmdesignerfields.cpp embeddedurlpage.cpp kincidencechooser.cpp
    groupwarejob.cpp pimemoticons.kcfgc krsqueezedtextlabel.cpp
    csshelper.cpp distributionlist.cpp kpimurlrequesterdlg.cpp
    sendsmsdialog.cpp kmailcompletion.cpp
  VERSION 1.0.0
  LINK kcal-shared kparts-shared kimproxy-shared ${QUI_LIBRARY}
  DESTINATION ${LIB_INSTALL_DIR}
)


##### install import cmake modules ###############

kde_install_export( )
