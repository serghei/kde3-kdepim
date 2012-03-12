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

include( FindPkgConfig )

# libical
pkg_search_module( LIBICAL libical )
if( LIBICAL_FOUND )
  if( NOT (LIBICAL_VERSION VERSION_LESS "0.46") )
    set( USE_LIBICAL_0_46 1 CACHE INTERNAL "" FORCE )
  endif( )
else( )
  kde_message_fatal( "libical are required, but not found on your system" )
endif()
