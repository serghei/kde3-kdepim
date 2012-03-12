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

add_subdirectory( protocols )
add_subdirectory( icons )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkdenetwork
  ${CMAKE_SOURCE_DIR}/kaddressbook/interfaces
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${CMAKE_SOURCE_DIR}/certmanager/lib
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
  ${GPGME_INCLUDE_DIRS}
)


##### other data ################################

install( FILES cryptosettings.desktop DESTINATION ${SERVICES_INSTALL_DIR}/kaddressbook )
install( FILES kaddressbookimprotocol.desktop DESTINATION ${SERVICETYPES_INSTALL_DIR} )


##### kabim (static) ############################

kde_add_library( kabim STATIC_PIC AUTOMOC
  SOURCES
    imeditorwidget.cpp imeditorbase.ui imaddressbase.ui imaddresswidget.cpp
)


##### libkaddrbk_cryptosettings (module) ########

kde_add_kpart( libkaddrbk_cryptosettings AUTOMOC
  SOURCES cryptowidget.cpp
  LINK kabinterfaces-shared kleopatra-shared kabc-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)
