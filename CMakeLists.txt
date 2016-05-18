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

cmake_minimum_required( VERSION 2.8 )


##### general package setup #####################

project( kdepim )
set( PACKAGE kdepim )
set( VERSION "3.6" )


##### optional stuff ############################

option( WITH_ALL_FEATURES "Enable all possible features" )
option( WITH_SASL "Enable cyrus-sasl support" ${WITH_ALL_FEATURES} )
option( WITH_NEWDISTRLISTS "Enable the new distribution lists" ${WITH_ALL_FEATURES} )
option( WITH_GNOKII "Enable gnokii support" ${WITH_ALL_FEATURES} )
option( WITH_EXCHANGE "Enable Microsoft Exchange 2000 support" ${WITH_ALL_FEATURES} )
option( WITH_EGROUPWARE "Enable egroupware support" ${WITH_ALL_FEATURES} )
option( WITH_KOLAB "Enable kolab support" ${WITH_ALL_FEATURES} )
option( WITH_SLOX "Enable slox support" ${WITH_ALL_FEATURES} )
option( WITH_GROUPWISE "Enable groupwise support" ${WITH_ALL_FEATURES} )
option( WITH_FEATUREPLAN "Enable featureplan support" ${WITH_ALL_FEATURES} )
option( WITH_GROUPDAV "Enable groupdav support" ${WITH_ALL_FEATURES} )
option( WITH_BIRTHDAYS "Enable birthdays support" ${WITH_ALL_FEATURES} )
option( WITH_NEWEXCHANGE "Enable newexchange support" ${WITH_ALL_FEATURES} )
option( WITH_SCALIX "Enable scalix support" ${WITH_ALL_FEATURES} )
option( WITH_INDEXLIB "Enable indexlib support (in kmail)" ${WITH_ALL_FEATURES} )

if( WITH_NEWDISTRLISTS )
  set( KDEPIM_NEW_DISTRLISTS 1 )
endif( )


##### user requested modules ####################

option( BUILD_ALL "Build all" OFF )
option( BUILD_INDEXLIB "Build indexlib" ${BUILD_ALL} )
option( BUILD_LIBKMIME "Build libkmime" ${BUILD_ALL} )
option( BUILD_KTNEF "Build ktnef" ${BUILD_ALL} )
option( BUILD_LIBKCAL "Build libkcal" ${BUILD_ALL} )
option( BUILD_LIBKDEPIM "Build libkdepim" ${BUILD_ALL} )
option( BUILD_LIBKPIMIDENTITIES "Build libkpimidentities" ${BUILD_ALL} )
option( BUILD_LIBKDENETWORK "Build libkdenetwork" ${BUILD_ALL} )
option( BUILD_CERTMANAGER "Build certmanager" ${BUILD_ALL} )
option( BUILD_LIBKPGP "Build libkpgp" ${BUILD_ALL} )
option( BUILD_MIMELIB "Build mimelib" ${BUILD_ALL} )
option( BUILD_LIBKSIEVE "Build libksieve" ${BUILD_ALL} )
option( BUILD_LIBKPIMEXCHANGE "Build libkpimexchange" ${BUILD_ALL} )
option( BUILD_KIOSLAVES "Build kioslaves" ${BUILD_ALL} )
option( BUILD_KMAIL "Build kmail" ${BUILD_ALL} )
option( BUILD_AKREGATOR "Build akregator" ${BUILD_ALL} )
option( BUILD_KALARM "Build kalarm" ${BUILD_ALL} )
option( BUILD_KADDRESSBOOK "Build kaddressbook" ${BUILD_ALL} )
option( BUILD_KORN "Build korn" ${BUILD_ALL} )
option( BUILD_KGANTT "Build kgantt" ${BUILD_ALL} )
option( BUILD_LIBKHOLIDAYS "Build libkholidays" ${BUILD_ALL} )
option( BUILD_KORGANIZER "Build korganizer" ${BUILD_ALL} )
option( BUILD_PLUGINS "Build plugins" ${BUILD_ALL} )
option( BUILD_KNOTES "Build knotes" ${BUILD_ALL} )
option( BUILD_KODE "Build kode" ${BUILD_ALL} )
option( BUILD_KRESOURCES "Build kresources" ${BUILD_ALL} )
option( BUILD_WIZARDS "Build wizards" ${BUILD_ALL} )
option( BUILD_KABC "Build kabc" ${BUILD_ALL} )
option( BUILD_KONSOLEKALENDAR "Build konsolekalendar" ${BUILD_ALL} )
option( BUILD_KMAILCVT "Build kmailcvt" ${BUILD_ALL} )
option( BUILD_KARM "Build karm" ${BUILD_ALL} )
option( BUILD_KFILE_PLUGINS "Build kfile-plugins" ${BUILD_ALL} )
option( BUILD_KANDY "Build kandy" ${BUILD_ALL} )
option( BUILD_KNODE "Build knode" ${BUILD_ALL} )
option( BUILD_KMOBILE "Build kmobile" ${BUILD_ALL} )
option( BUILD_DOC "Build doc" ${BUILD_ALL} )
option( BUILD_KONTACT "Build kontact" ${BUILD_ALL} )

# deprecated
option( BUILD_KITCHENSYNC "Build kitchensync" OFF )


##### configure checks ##########################

include( ConfigureChecks.cmake )


##### activate dependencies #####################

if( BUILD_LIBKCAL OR BUILD_LIBKDEPIM OR BUILD_LIBKPIMIDENTITIES OR BUILD_KIOSLAVES OR BUILD_KMAIL OR BUILD_KNODE )
  add_subdirectory( libemailfunctions )
endif()

if( BUILD_KADDRESSBOOK OR (BUILD_KRESOURCES AND (WITH_EGROUPWARE OR WITH_BIRTHDAYS)) )
    add_subdirectory( kaddressbook/common )
endif()


##### kdepim directories ########################

kde_conditional_add_subdirectory( BUILD_INDEXLIB indexlib )
kde_conditional_add_subdirectory( BUILD_LIBKMIME libkmime )
kde_conditional_add_subdirectory( BUILD_KTNEF ktnef )
kde_conditional_add_subdirectory( BUILD_LIBKCAL libkcal )
kde_conditional_add_subdirectory( BUILD_LIBKDEPIM pixmaps )
kde_conditional_add_subdirectory( BUILD_LIBKDEPIM libkdepim )
kde_conditional_add_subdirectory( BUILD_LIBKPIMIDENTITIES libkpimidentities )
kde_conditional_add_subdirectory( BUILD_LIBKDENETWORK libkdenetwork )
kde_conditional_add_subdirectory( BUILD_CERTMANAGER certmanager )
kde_conditional_add_subdirectory( BUILD_LIBKPGP libkpgp )
kde_conditional_add_subdirectory( BUILD_MIMELIB mimelib )
kde_conditional_add_subdirectory( BUILD_LIBKSIEVE libksieve )
kde_conditional_add_subdirectory( BUILD_LIBKPIMEXCHANGE libkpimexchange )
kde_conditional_add_subdirectory( BUILD_KIOSLAVES kioslaves )
kde_conditional_add_subdirectory( BUILD_KMAIL kmail )
kde_conditional_add_subdirectory( BUILD_AKREGATOR akregator )
kde_conditional_add_subdirectory( BUILD_KALARM kalarm )
kde_conditional_add_subdirectory( BUILD_KADDRESSBOOK kaddressbook )
kde_conditional_add_subdirectory( BUILD_KORN korn )
kde_conditional_add_subdirectory( BUILD_KGANTT kgantt )
kde_conditional_add_subdirectory( BUILD_LIBKHOLIDAYS libkholidays )
kde_conditional_add_subdirectory( BUILD_KORGANIZER kdgantt )
kde_conditional_add_subdirectory( BUILD_KORGANIZER korganizer )
kde_conditional_add_subdirectory( BUILD_PLUGINS plugins )
kde_conditional_add_subdirectory( BUILD_KNOTES knotes )
kde_conditional_add_subdirectory( BUILD_KODE kode )
kde_conditional_add_subdirectory( BUILD_KRESOURCES kresources )
kde_conditional_add_subdirectory( BUILD_WIZARDS wizards )
kde_conditional_add_subdirectory( BUILD_KABC kabc )
kde_conditional_add_subdirectory( BUILD_KONSOLEKALENDAR konsolekalendar )
kde_conditional_add_subdirectory( BUILD_KMAILCVT kmailcvt )
kde_conditional_add_subdirectory( BUILD_KARM karm )
kde_conditional_add_subdirectory( BUILD_KFILE_PLUGINS kfile-plugins )
kde_conditional_add_subdirectory( BUILD_KANDY kandy )
kde_conditional_add_subdirectory( BUILD_KNODE knode )
kde_conditional_add_subdirectory( BUILD_KMOBILE kmobile )
kde_conditional_add_subdirectory( BUILD_KITCHENSYNC kitchensync )
kde_conditional_add_subdirectory( BUILD_DOC doc )
kde_conditional_add_subdirectory( BUILD_KONTACT kontact )


##### write configure files #####################

configure_file( config.h.cmake config.h @ONLY )
