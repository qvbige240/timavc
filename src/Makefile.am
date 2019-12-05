
pkginclude_HEADERS = \
    avc/avc.h

lib_LTLIBRARIES=libavc.la

libavc_la_CFLAGS = -I$(top_srcdir)/src/vmp -I$(top_srcdir)/src/support
libavc_la_SOURCES=\
    avc/avc.c \
    avc/avc_core.c \
    avc/avc_core.h \
    avc/avc_demo.c \
    avc/avc_demo.h \
    avc/avc.h \
    avc/avc_typedef.h \
    support/globals.c \
    support/globals.h \
    support/module_logger.c \
    support/module_logger.h \
    support/module_support.h \
    vmp/vmp.h \
    vmp/vmp_log.h \
    vmp/vmp_typedef.h \
    $(pkg_include_HEADERS)

libavc_la_LDFLAGS = -version-info $(LIBAVC_VERSION_INFO) $(LDFLAGS_NOUNDEFINED)

