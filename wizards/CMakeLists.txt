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

# Possible options:
# - WITH_EGROUPWARE
# - WITH_SLOX
# - WITH_KOLAB
# - WITH_NEWEXCHANGE
# - WITH_GROUPWISE
# - WITH_SCALIX

kde_import( libkmime )
kde_import( ktnef )
kde_import( libkcal )
kde_import( libkdepim )
kde_import( knotes )
kde_import( kresources )

if( WITH_KOLAB OR WITH_GROUPWISE OR WITH_SCALIX )
  kde_import( libkdenetwork )
  kde_import( certmanager )
  kde_import( libkpimidentities )
endif()

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkpimidentities
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${CMAKE_SOURCE_DIR}/certmanager/lib
  ${CMAKE_SOURCE_DIR}/knotes
  ${CMAKE_SOURCE_DIR}/kresources/lib
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

install( FILES
    groupwarewizard.desktop
  DESTINATION ${XDG_APPS_INSTALL_DIR} )


##### helper ####################################

macro( process_kcfg _who _out _path _kcfg _kcfgc )
  add_custom_command( OUTPUT ${CMAKE_BINARY_DIR}/${_path}/${_out}
    COMMAND
      mkdir -p ${CMAKE_BINARY_DIR}/${_path}
    COMMAND ${KDE3_KCFGC_EXECUTABLE}
      -d ${CMAKE_BINARY_DIR}/${_path}
      ${CMAKE_SOURCE_DIR}/${_path}/${_kcfg}
      ${CMAKE_SOURCE_DIR}/${_path}/${_kcfgc}
    DEPENDS
      ${CMAKE_SOURCE_DIR}/${_path}/${_kcfg}
      ${CMAKE_SOURCE_DIR}/${_path}/${_kcfgc} )
  set_property( SOURCE ${_who} APPEND
    PROPERTY OBJECT_DEPENDS ${CMAKE_BINARY_DIR}/${_path}/${_out} )
endmacro()


######## egroupwarewizard #######################

if( WITH_EGROUPWARE )

  install( FILES egroupware.kcfg DESTINATION ${KCFG_INSTALL_DIR} )

  process_kcfg( egroupwarewizard.cpp kabc_egroupwareprefs.h kresources/egroupware
    kresources_kabc_egroupware.kcfg kabc_egroupwareprefs.kcfgc )

  process_kcfg( egroupwarewizard.cpp kcal_egroupwareprefs.h kresources/egroupware
    kresources_kcal_egroupware.kcfg kcal_egroupwareprefs.kcfgc )

  process_kcfg( egroupwarewizard.cpp knotes_egroupwareprefs.h kresources/egroupware
    kresources_knotes_egroupware.kcfg knotes_egroupwareprefs.kcfgc )

  kde_add_library( egroupwarewizard SHARED NO_EXPORT
    SOURCES
      egroupwarewizard.cpp egroupwareconfig.kcfgc
    LINK kcal_xmlrpc-shared kabc_xmlrpc-shared knotes_xmlrpc-shared
    DESTINATION ${PLUGIN_INSTALL_DIR} )

  kde_add_executable( egroupwarewizard
    SOURCES egroupwaremain.cpp
    LINK egroupwarewizard-shared
    DESTINATION ${BIN_INSTALL_DIR} )

  set( EGROUPWAREWIZARD_LIBRARY egroupwarewizard-shared )

endif()


######## sloxwizard #############################

if( WITH_SLOX )

  install( FILES slox.kcfg DESTINATION ${KCFG_INSTALL_DIR} )

  process_kcfg( sloxwizard.cpp kabcsloxprefs.h kresources/slox
    kresources_kabc_slox.kcfg kabcsloxprefs.kcfgc )

  process_kcfg( sloxwizard.cpp kcalsloxprefs.h kresources/slox
    kresources_kcal_slox.kcfg kcalsloxprefs.kcfgc )

  kde_add_library( sloxwizard SHARED NO_EXPORT
    SOURCES
      sloxwizard.cpp sloxconfig.kcfgc
    LINK kcal_slox-shared kabc_slox-shared
    DESTINATION ${PLUGIN_INSTALL_DIR} )

  kde_add_executable( sloxwizard
    SOURCES sloxmain.cpp
    LINK sloxwizard-shared
    DESTINATION ${BIN_INSTALL_DIR} )

  set( SLOXWIZARD_LIBRARY sloxwizard-shared )

endif()


######## kolabwizard ############################

if( WITH_KOLAB )

  install( FILES kolab.kcfg DESTINATION ${KCFG_INSTALL_DIR} )

  kde_add_library( kolabwizard SHARED NO_EXPORT
    SOURCES
      kolabwizard.cpp kmailchanges.cpp kolabconfig.kcfgc
      kolabkmailchanges.cpp
    LINK
      kcalkolab-shared kabckolab-shared knoteskolab-shared
      kpimidentities-shared
    DESTINATION ${PLUGIN_INSTALL_DIR} )

  kde_add_executable( kolabwizard
    SOURCES kolabmain.cpp
    LINK kolabwizard-shared
    DESTINATION ${BIN_INSTALL_DIR} )

  set( KOLABWIZARD_LIBRARY kolabwizard-shared )

endif( )


######## exchangewizard #########################

if( WITH_NEWEXCHANGE )

  kde_add_library( exchangewizard SHARED NO_EXPORT
    SOURCES exchangewizard.cpp
    LINK kcal_newexchange-shared
    DESTINATION ${PLUGIN_INSTALL_DIR} )

  kde_add_executable( exchangewizard
    SOURCES exchangemain.cpp
    LINK exchangewizard-shared
    DESTINATION ${BIN_INSTALL_DIR} )

  set( EXCHANGEWIZARD_LIBRARY exchangewizard-shared )

endif()


######## groupwisewizard ########################

if( WITH_GROUPWISE )

  install( FILES groupwise.kcfg DESTINATION ${KCFG_INSTALL_DIR} )

  process_kcfg( groupwisewizard.cpp kcal_groupwiseprefsbase.h kresources/groupwise
    kresources_kcal_groupwise.kcfg kcal_groupwiseprefsbase.kcfgc )

  process_kcfg( groupwisewizard.cpp kabc_groupwiseprefs.h kresources/groupwise
    kresources_kabc_groupwise.kcfg kabc_groupwiseprefs.kcfgc )

  kde_add_library( groupwisewizard SHARED AUTOMOC NO_EXPORT
    SOURCES
      groupwisewizard.cpp groupwiseconfig.kcfgc kmailchanges.cpp
    LINK kcal_groupwise-shared kabc_groupwise-shared kpimidentities-shared
    DESTINATION ${PLUGIN_INSTALL_DIR} )

  kde_add_executable( groupwisewizard
    SOURCES groupwisemain.cpp
    LINK groupwisewizard-shared
    DESTINATION ${BIN_INSTALL_DIR} )

  set( GROUPWISE_LIBRARY groupwisewizard-shared )

endif()


######## scalixwizard ###########################

if( WITH_SCALIX )

  install( FILES scalix.kcfg DESTINATION ${KCFG_INSTALL_DIR} )

  kde_add_library( scalixwizard SHARED NO_EXPORT
    SOURCES
      scalixwizard.cpp kmailchanges.cpp scalixconfig.kcfgc
      scalixkmailchanges.cpp
    LINK kcalscalix-shared kabcscalix-shared kpimidentities-shared
    DESTINATION ${PLUGIN_INSTALL_DIR} )

  kde_add_executable( scalixwizard
    SOURCES scalixmain.cpp
    LINK scalixwizard-shared
    DESTINATION ${BIN_INSTALL_DIR} )

endif()


##### groupwarewizard (executable) ##############

if( WITH_EGROUPWARE OR WITH_SLOX OR WITH_KOLAB OR WITH_NEWEXCHANGE )

  configure_file( wizards-config.h.cmake wizards-config.h @ONLY )

  kde_add_executable( groupwarewizard AUTOMOC
    SOURCES
      groupwarewizard.cpp main.cpp overviewpage.cpp
    LINK
      ${EGROUPWAREWIZARD_LIBRARY} ${SLOXWIZARD_LIBRARY}
      ${KOLABWIZARD_LIBRARY} ${EXCHANGEWIZARD_LIBRARY} ${GROUPWISE_LIBRARY}
    DESTINATION ${BIN_INSTALL_DIR} )

endif()
