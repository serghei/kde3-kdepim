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

# NOTE is needed libopensync-0.22

pkg_search_module( OPENSYNC opensync-1.0 )
if( NOT OPENSYNC_FOUND )
  kde_message_fatal( "opensync-1.0 is requested, but was not found on your system" )
endif( )

pkg_search_module( OSENGINE osengine-1.0 )
if( NOT OSENGINE_FOUND )
  kde_message_fatal( "osengine-1.0 is requested, but was not found on your system" )
endif( )
