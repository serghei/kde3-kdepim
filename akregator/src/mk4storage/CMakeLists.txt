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

add_subdirectory( metakit )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/akregator/src
  ${CMAKE_SOURCE_DIR}/akregator/src/mk4storage/metakit/include
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

install( FILES akregator_mk4storage_plugin.desktop DESTINATION ${SERVICES_INSTALL_DIR} )
install( FILES mk4config.kcfg DESTINATION ${KCFG_INSTALL_DIR} )


##### libakregator_mk4storage_plugin (module)  ##

kde_add_kpart( libakregator_mk4storage_plugin AUTOMOC
  SOURCES
    feedstoragemk4impl.cpp mk4plugin.cpp storagemk4impl.cpp
    storagefactorymk4impl.cpp
  LINK
    rsslocal-static metakitlocal-static
    akregatorprivate-shared kio-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)
