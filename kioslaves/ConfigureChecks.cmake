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

if( WITH_SASL )
  include( CheckIncludeFile )
  include( CheckLibraryExists )
  check_include_file( sasl/sasl.h HAVE_SASL_SASL_H )
  if( HAVE_SASL_SASL_H )
    check_library_exists( sasl2 sasl_client_init "" HAVE_LIBSASL2 )
  endif( )
  if( HAVE_LIBSASL2 )
    set( SASL_LIBRARY sasl2 CACHE INTERNAL "" )
  else( )
    kde_message_fatal( "cyrus-sasl is required, but not found on your system" )
  endif( )
endif( )
