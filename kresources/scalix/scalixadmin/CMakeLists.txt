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
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### scalixadmin (executable) ##################

kde_add_executable( scalixadmin AUTOMOC
  SOURCES
    main.cpp mainwindow.cpp passwordpage.cpp settings.cpp jobs.cpp
    otherusermanager.cpp otheruserview.cpp otheruserpage.cpp ldapview.cpp
    ldapdialog.cpp delegatemanager.cpp delegateview.cpp delegatepage.cpp
    delegatedialog.cpp outofofficepage.cpp
  LINK kabc-shared
  DESTINATION ${BIN_INSTALL_DIR}
)
