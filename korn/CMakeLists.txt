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

# FIXME KDE_CXXFLAGS = $(USE_RTTI)

kde_import( libkmime )

add_subdirectory( kconf_update )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkmime
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

kde_install_icons( korn )
install( FILES KOrn.desktop DESTINATION ${XDG_APPS_INSTALL_DIR} )


##### korn (executable) #########################

kde_add_executable( korn AUTOMOC
  SOURCES
    accountmanager.cpp account_input.cpp boxcontainer.cpp boxcontaineritem.cpp
    boxcontaineritem.skel dcopdrop.cpp dcopdropif.cpp dcopdropif.skel
    dcop_proto.cpp dockedcontainer.cpp dockeditem.cpp hvcontainer.cpp hvitem.cpp
    keditlistboxman.cpp nntp_proto.cpp maildrop.cpp main.cpp polldrop.cpp
    protocols.cpp kornshell.cpp subjectsdlg.cpp maildlg.cpp mailid.cpp
    mailsubject.cpp mbox_proto.cpp imap_proto.cpp intid.cpp stringid.cpp
    kornapp.cpp kio.cpp kio_count.cpp kio_proto.cpp kio_subjects.cpp
    kio_single_subject.cpp kio_read.cpp kio_delete.cpp kmail_proto.cpp
    sortedmailsubject.cpp korncfgimpl.cpp kornaccountcfgimpl.cpp kornboxcfgimpl.cpp
    kornaccountcfg.ui kornboxcfg.ui korncfg.ui password.cpp pop3_proto.cpp
    systemtray.cpp process_proto.cpp progress_dialog.ui qmail_proto.cpp label.cpp
  LINK kmime-shared kio-shared
  DESTINATION ${BIN_INSTALL_DIR}
)
