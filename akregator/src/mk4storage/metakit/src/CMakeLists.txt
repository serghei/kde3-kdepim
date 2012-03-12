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
  ${CMAKE_CURRENT_SOURCE_DIR}/../include
  ${CMAKE_BINARY_DIR}
  ${KDE_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)


##### metakitlocal (static) #####################

kde_add_library( metakitlocal STATIC_PIC
  SOURCES
    column.cpp custom.cpp derived.cpp field.cpp fileio.cpp
    format.cpp handler.cpp persist.cpp remap.cpp std.cpp
    store.cpp string.cpp table.cpp univ.cpp view.cpp viewx.cpp
)
