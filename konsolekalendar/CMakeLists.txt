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

kde_import( libkmime )
kde_import( ktnef )
kde_import( libkcal )
kde_import( libkdepim )

add_subdirectory( pixmaps )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### other data ################################

install( FILES konsolekalendar.desktop DESTINATION ${XDG_APPS_INSTALL_DIR} )


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
endmacro( )


##### konsolekalendar (executable) ##############

process_kcfg( konsolekalendar.cpp htmlexportsettings.h libkcal
  htmlexportsettings.kcfg htmlexportsettings.kcfgc )

kde_add_executable( konsolekalendar AUTOMOC
  SOURCES
    konsolekalendarepoch.cpp konsolekalendardelete.cpp
    konsolekalendarchange.cpp konsolekalendarvariables.cpp
    konsolekalendaradd.cpp konsolekalendarexports.cpp konsolekalendar.cpp
    stdcalendar.cpp main.cpp
  LINK kdepim-shared
  DESTINATION ${BIN_INSTALL_DIR}
)
