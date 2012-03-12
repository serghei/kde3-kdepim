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

project( ktnef )
include( ConfigureChecks.cmake )

add_subdirectory( ktnef )
add_subdirectory( lib )
add_subdirectory( gui )

kde_install_export( )
