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

project( libkdenetwork )

add_subdirectory( gpgmepp )
add_subdirectory( qgpgme )


##### install import cmake modules ###############

kde_install_export( )
