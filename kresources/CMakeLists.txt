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

project( kresources )

kde_import( libkmime )
kde_import( ktnef )
kde_import( libkcal )
kde_import( libkdepim )
kde_import( knotes )

add_subdirectory( lib )
add_subdirectory( remote )
kde_conditional_add_subdirectory( WITH_EGROUPWARE egroupware )
kde_conditional_add_subdirectory( WITH_EXCHANGE exchange )
kde_conditional_add_subdirectory( WITH_KOLAB kolab )
kde_conditional_add_subdirectory( WITH_SLOX slox )
kde_conditional_add_subdirectory( WITH_GROUPWISE groupwise )
kde_conditional_add_subdirectory( WITH_FEATUREPLAN featureplan )
kde_conditional_add_subdirectory( WITH_GROUPDAV groupdav )
kde_conditional_add_subdirectory( WITH_BIRTHDAYS birthdays )
kde_conditional_add_subdirectory( WITH_NEWEXCHANGE newexchange )
kde_conditional_add_subdirectory( WITH_SCALIX scalix )

kde_install_export( )
