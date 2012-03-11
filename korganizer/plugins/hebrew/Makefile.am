# $Id: Makefile.am 242335 2003-08-12 19:33:21Z jsinger $

METASOURCES = AUTO

INCLUDES = -I$(top_srcdir)/korganizer/interfaces $(all_includes)

kde_module_LTLIBRARIES = libkorg_hebrew.la

libkorg_hebrew_la_SOURCES = hebrew.cpp configdialog.cpp holiday.cpp parsha.cpp converter.cpp
libkorg_hebrew_la_LDFLAGS = -module $(KDE_PLUGIN) $(KDE_RPATH) $(all_libraries) 
libkorg_hebrew_la_LIBADD = $(LIB_KDECORE) $(LIB_KDEUI)

noinst_HEADERS = hebrew.h configdialog.h parsha.h converter.h holiday.h

servicedir  = $(kde_servicesdir)/korganizer
service_DATA = hebrew.desktop
