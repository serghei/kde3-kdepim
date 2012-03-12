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

include( CheckIncludeFileCXX )

kde_save( CMAKE_CXX_FLAGS CMAKE_REQUIRED_INCLUDES )
unset( CMAKE_CXX_FLAGS )
set( CMAKE_REQUIRED_INCLUDES ${BOOST_INCLUDE_DIR} )

check_include_file_cxx( "boost/format.hpp" HAVE_BOOST )

if( NOT HAVE_BOOST )
  kde_message_fatal( "boost library is required, but was not found on your system.\n Try to set boost include dir to BOOST_INCLUDE_DIR." )
endif( )

kde_restore( CMAKE_CXX_FLAGS CMAKE_REQUIRED_INCLUDES )
