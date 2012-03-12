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
  ${CMAKE_CURRENT_BINARY_DIR}/../lib
  ${CMAKE_CURRENT_SOURCE_DIR}/../lib
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

install( FILES kcal_newexchange.desktop DESTINATION ${SERVICES_INSTALL_DIR}/kresources/kcal )
install( FILES kabc_newexchange.desktop DESTINATION ${SERVICES_INSTALL_DIR}/kresources/kabc )


##### kcal_newexchange (module) #################

kde_add_kpart( kcal_newexchange AUTOMOC
  SOURCES kcal_resourceexchange_plugin.cpp
  LINK kcal_newexchange-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### kabc_newexchange (module) #################

kde_add_kpart( kabc_newexchange AUTOMOC
  SOURCES kabc_resourceexchange_plugin.cpp
  LINK kabc_newexchange-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### knewexchange (static) #####################

kde_add_library( knewexchange STATIC_PIC
  SOURCES
    exchangeglobals.cpp exchangeconvertercalendar.cpp
    exchangeconvertercontact.cpp
)


##### kcal_newexchange (shared) #################

kde_add_library( kcal_newexchange SHARED AUTOMOC
  SOURCES
    exchangecalendaradaptor.cpp kcal_resourceexchange.cpp
  VERSION 1.0.0
  LINK knewexchange-static kgroupwaredav-shared
  DESTINATION ${LIB_INSTALL_DIR}
)


##### kabc_newexchange (shared) #################

kde_add_library( kabc_newexchange SHARED AUTOMOC
  SOURCES
    exchangeaddressbookadaptor.cpp kabc_resourceexchange.cpp
  VERSION 1.0.0
  LINK knewexchange-static kgroupwaredav-shared
  DESTINATION ${LIB_INSTALL_DIR}
)
