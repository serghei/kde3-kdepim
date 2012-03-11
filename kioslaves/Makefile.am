## $Id: Makefile.am 427821 2005-06-21 23:40:49Z adridg $

if compile_kio_sieve
  SIEVE_SUBDIR = sieve
endif

SUBDIRS = imap4 mbox $(SIEVE_SUBDIR)

DOXYGEN_REFERENCES = kioslaves/imap4 kioslaves/mbox
include $(top_srcdir)/admin/Doxyfile.am

