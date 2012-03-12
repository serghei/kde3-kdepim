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
kde_import( ktnef )
kde_import( libkcal )
kde_import( libkdepim )

kde_import( libksieve )
kde_import( mimelib )
kde_import( libkdenetwork )
kde_import( certmanager )
kde_import( libkpimidentities )
kde_import( libkpgp )
kde_import( kmail )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/libkdepim
  ${CMAKE_SOURCE_DIR}/mimelib
  ${CMAKE_SOURCE_DIR}/libkmime
  ${CMAKE_SOURCE_DIR}/libemailfunctions
  ${CMAKE_SOURCE_DIR}/kmail
  ${CMAKE_SOURCE_DIR}/korganizer
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)

link_directories(
  ${QT_LIBRARY_DIR}
)


##### other data ################################

install( FILES
    text_vcard.desktop text_calendar.desktop text_xdiff.desktop
  DESTINATION ${DATA_INSTALL_DIR}/kmail/plugins/bodypartformatter )


##### libkmail_bodypartformatter_text_vcard (module)

kde_add_kpart( libkmail_bodypartformatter_text_vcard AUTOMOC
  SOURCES
    text_vcard.cpp
  LINK kdepim-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### libkmail_bodypartformatter_text_calendar (module)

kde_add_kpart( libkmail_bodypartformatter_text_calendar AUTOMOC
  SOURCES
    text_calendar.cpp delegateselector.cpp attendeeselector.cpp
    ui_attendeeselector.ui ${CMAKE_SOURCE_DIR}/korganizer/kcalendariface.stub
  LINK kmailprivate-shared
  DESTINATION ${PLUGIN_INSTALL_DIR}
)


##### libkmail_bodypartformatter_text_xdiff (module)

kde_add_kpart( libkmail_bodypartformatter_text_xdiff AUTOMOC
  SOURCES
    text_xdiff.cpp
  LINK ${QT_LIBRARY}
  DESTINATION ${PLUGIN_INSTALL_DIR}
)
