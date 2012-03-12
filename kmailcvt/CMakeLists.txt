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

add_subdirectory( pics )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_BINARY_DIR}
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

kde_install_icons( )

install(
  FILES uninstall.desktop
  RENAME kmailcvt.desktop
  DESTINATION ${APPS_INSTALL_DIR}/Utilities )


##### kmailcvt (executable) #####################

kde_add_executable( kmailcvt AUTOMOC
  SOURCES
    kimportpagedlg.ui kimportpage.cpp kselfilterpagedlg.ui
    kselfilterpage.cpp filters.cxx filter_oe.cxx kmailcvt.cpp main.cpp
    filter_pmail.cxx filter_plain.cxx filter_outlook.cxx filter_mbox.cxx
    filter_evolution.cxx filter_mailapp.cxx filter_evolution_v2.cxx
    filter_opera.cxx filter_thunderbird.cxx filter_kmail_maildir.cxx
    filter_sylpheed.cxx filter_thebat.cxx filter_lnotes.cxx
  LINK kio-shared
  DESTINATION ${BIN_INSTALL_DIR}
)
