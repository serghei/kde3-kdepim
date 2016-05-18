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

include( CheckIncludeFile )
include( FindPkgConfig )

# find kdelibs
# FIXME should be more flexibile
set( CMAKE_MODULE_PATH "${CMAKE_INSTALL_PREFIX}/share/cmake" )
if( NOT EXISTS "${CMAKE_MODULE_PATH}/FindKDE3.cmake" )
  message( FATAL_ERROR
      "\n"
      "####################################################################\n "
      "${CMAKE_MODULE_PATH}/FindKDE3.cmake does not exists.\n "
      "Please pass corect CMAKE_INSTALL_PREFIX to cmake.\n"
      "####################################################################\n" )
endif( )
include( FindKDE3 )


if( BUILD_LIBKDEPIM OR BUILD_KMAIL )
  option( KDEPIM_NEW_DISTRLISTS "Define if you want to use the new distribution lists" ON )
endif( )


if( BUILD_INDEXLIB OR BUILD_KMAIL )

  include( CheckCXXSourceCompiles )

  # check for stl coping with namespace std
  check_cxx_source_compiles("
      #include <iterator>
      struct s : public std::iterator<std::forward_iterator_tag, int> {};
      int main(int, char**) { return 0; } "
      HAVE_STLNAMESPACE )
  if( HAVE_STLNAMESPACE )
    set( STD_NAMESPACE_PREFIX "std::" )
  endif( )

endif( )


if( BUILD_KMOBILE )
  # FIXME not checked because Gentoo don't provide baudboy.h
  check_include_file( "baudboy.h" HAVE_BAUDBOY_H )
endif( )


if( BUILD_KANDY OR (BUILD_KMOBILE AND NOT HAVE_BAUDBOY_H) )
  check_include_file( "lockdev.h" HAVE_LOCKDEV_H )
  if( HAVE_LOCKDEV_H )
    check_library_exists( lockdev dev_unlock "" HAVE_LOCKDEV )
    if( HAVE_LOCKDEV )
      set( LOCKDEV_LIBRARY lockdev CACHE INTERNAL "" FORCE )
    endif( )
  endif( )
endif( )


if( BUILD_LIBKDENETWORK OR BUILD_CERTMANAGER OR BUILD_KMAIL OR BUILD_KADDRESSBOOK OR BUILD_KONTACT )

  if( NOT HAVE_GPGME_0_4_BRANCH )
    message( STATUS "checking for 'gpgme'" )
  endif( )

  # find gpgme-config
  find_program( GPGME_EXECUTABLE NAMES gpgme-config )
  if( NOT GPGME_EXECUTABLE )
    kde_message_fatal( "gpgme-config are NOT found.\n gpgme library are installed?" )
  endif( )

  macro( __run_gpgme_config  __type __var )
    execute_process(
      COMMAND ${GPGME_EXECUTABLE} --${__type}
      OUTPUT_VARIABLE ${__var}
      RESULT_VARIABLE __result
      OUTPUT_STRIP_TRAILING_WHITESPACE )
    if( _result )
      kde_message_fatal( "Unable to run ${GPGME_EXECUTABLE}!\n gpgme library are correctly installed?\n Path to gpgme-config are corect?" )
    endif( )
  endmacro( )

  __run_gpgme_config( version GPGME_VERSION )
  __run_gpgme_config( cflags GPGME_INCLUDE_DIRS )
  __run_gpgme_config( libs GPGME_LIBRARIES )

  # cleanup
  if( GPGME_INCLUDE_DIRS )
    string( REGEX REPLACE "(^| )-I" ";" GPGME_INCLUDE_DIRS "${GPGME_INCLUDE_DIRS}" )
  endif( )
  if( GPGME_LIBRARIES )
    string( REGEX REPLACE "(^| )-l" ";" GPGME_LIBRARIES "${GPGME_LIBRARIES}" )
  endif( )

  find_library( GPG_ERROR_LIBRARY NAMES "gpg-error" )

  # assuming that all newer system have gpgme >= 0.4
  set( HAVE_GPGME_0_4_BRANCH 1 CACHE INTERNAL "" )

  # NOTE: assume we have largefile support (need for gpgme)
  # FIXME: to be sure, we should check it
  add_definitions( -D_FILE_OFFSET_BITS=64 )

  if( NOT HAVE_GPGME_0_4_BRANCH )
    message( STATUS "  found 'gpgme', version ${GPGME_VERSION}" )
  endif( )
endif( )
