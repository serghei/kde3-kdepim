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
  ${CMAKE_SOURCE_DIR}/libkpgp
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
  ${GPGME_INCLUDE_DIRS}
)


##### headers ###################################

install( FILES
    kdhorizontalline.h messagebox.h progressbar.h
    progressdialog.h keylistview.h keyselectiondialog.h
    keyrequester.h passphrasedialog.h keyapprovaldialog.h
    backendconfigwidget.h dnattributeorderconfigwidget.h
  DESTINATION ${INCLUDE_INSTALL_DIR}/kleo )


##### kleopatra_ui (static) #####################

kde_add_library( kleopatra_ui STATIC_PIC AUTOMOC
  SOURCES
    kdhorizontalline.cpp messagebox.cpp progressbar.cpp
    progressdialog.cpp keylistview.cpp keyselectiondialog.cpp
    keyrequester.cpp passphrasedialog.cpp keyapprovaldialog.cpp
    backendconfigwidget.cpp dnattributeorderconfigwidget.cpp
    cryptoconfigmodule.cpp cryptoconfigdialog.cpp
    directoryserviceswidgetbase.ui directoryserviceswidget.cpp
    adddirectoryservicedialog.ui adddirectoryservicedialogimpl.cpp
)
