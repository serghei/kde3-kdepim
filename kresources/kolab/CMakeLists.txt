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

add_subdirectory( shared )
add_subdirectory( kabc )
add_subdirectory( knotes )
add_subdirectory( kcal )

install( FILES kolab-resource.upd DESTINATION ${DATA_INSTALL_DIR}/kconf_update )
install( PROGRAMS upgrade-resourcetype.pl DESTINATION ${DATA_INSTALL_DIR}/kconf_update )
