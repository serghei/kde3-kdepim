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
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/kaddressbook
  ${CMAKE_SOURCE_DIR}/kaddressbook/interfaces
  ${CMAKE_SOURCE_DIR}/libkdenetwork
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

install( FILES
    csv_xxport.desktop vcard_xxport.desktop kde2_xxport.desktop
    bookmark_xxport.desktop eudora_xxport.desktop ldif_xxport.desktop
    opera_xxport.desktop pab_xxport.desktop
  DESTINATION ${SERVICES_INSTALL_DIR}/kaddressbook )

install( FILES
    csv_xxportui.rc vcard_xxportui.rc kde2_xxportui.rc bookmark_xxportui.rc
    eudora_xxportui.rc ldif_xxportui.rc opera_xxportui.rc pab_xxportui.rc
  DESTINATION ${DATA_INSTALL_DIR}/kaddressbook )


##### libkaddrbk_csv_xxport (module) ############

kde_add_kpart( libkaddrbk_csv_xxport AUTOMOC
  SOURCES csv_xxport.cpp csvimportdialog.cpp dateparser.cpp
  LINK kabinterfaces-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### libkaddrbk_vcard_xxport (module) ##########

kde_add_kpart( libkaddrbk_vcard_xxport AUTOMOC
  SOURCES vcard_xxport.cpp
  LINK kaddressbook-shared qgpgme-shared kabinterfaces-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### libkaddrbk_kde2_xxport (module) ###########

kde_add_kpart( libkaddrbk_kde2_xxport AUTOMOC
  SOURCES kde2_xxport.cpp
  LINK kabinterfaces-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### libkaddrbk_bookmark_xxport (module) #######

kde_add_kpart( libkaddrbk_bookmark_xxport AUTOMOC
  SOURCES bookmark_xxport.cpp
  LINK kabinterfaces-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### libkaddrbk_eudora_xxport (module) #########

kde_add_kpart( libkaddrbk_eudora_xxport AUTOMOC
  SOURCES eudora_xxport.cpp
  LINK kabinterfaces-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### libkaddrbk_ldif_xxport (module) ###########

kde_add_kpart( libkaddrbk_ldif_xxport AUTOMOC
  SOURCES ldif_xxport.cpp
  LINK kabinterfaces-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### libkaddrbk_opera_xxport (module) ##########

kde_add_kpart( libkaddrbk_opera_xxport AUTOMOC
  SOURCES opera_xxport.cpp
  LINK kabinterfaces-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### libkaddrbk_pab_xxport (module) ############

kde_add_kpart( libkaddrbk_pab_xxport AUTOMOC
  SOURCES pab_xxport.cpp pab_mapihd.cpp pab_pablib.cpp
  LINK kabinterfaces-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)
