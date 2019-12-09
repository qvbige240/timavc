LDADD = ../src/libavc.la $(STATIC_LIBS) $(DYNAMIC_LIBS) 
AM_LDFLAGS = -L$(top_builddir)/src/.libs
AM_CPPFLAGS = -I$(top_srcdir) -I$(top_srcdir)/include -I$(top_srcdir)/src

noinst_PROGRAMS = timavc
timavc_CFLAGS = -I$(top_srcdir)/src/vmp -I$(top_srcdir)/src/support -I$(top_srcdir)/src/avc
timavc_SOURCES = main.c

verify:

DISTCLEANFILES = *~