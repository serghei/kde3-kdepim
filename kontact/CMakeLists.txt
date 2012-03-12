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

kde_import( libkdenetwork )
kde_import( libkmime )
kde_import( ktnef )
kde_import( libkcal )
kde_import( libkdepim )
kde_import( certmanager )
kde_import( libkpimidentities )

add_subdirectory( interfaces )
add_subdirectory( plugins )
add_subdirectory( src )
add_subdirectory( pics )
add_subdirectory( profiles )
