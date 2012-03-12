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

include( ConfigureChecks.cmake )

add_subdirectory( imap4 )
add_subdirectory( mbox )

if( WITH_SASL )
  add_subdirectory( sieve )
else( )
  message( "*** sieve kioslave will not be built (because lack of sasl support)" )
endif( )
