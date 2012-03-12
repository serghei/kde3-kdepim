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
include( CheckTypeSize )

check_include_file( inttypes.h HAVE_INTTYPES_H )
check_include_file( stdint.h HAVE_STDINT_H )

check_type_size( "unsigned long long" SIZEOF_UNSIGNED_LONG_LONG )
check_type_size( "unsigned long" SIZEOF_UNSIGNED_LONG )
check_type_size( "uint64_t" SIZEOF_UINT64_T )
