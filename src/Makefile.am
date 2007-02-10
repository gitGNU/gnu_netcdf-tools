### Makefile.am  -*- Makefile -*-

bin_PROGRAMS = hdfdump

AM_CFLAGS = -Wall
AM_CPPFLAGS = -I$(top_builddir)/lib -I$(top_srcdir)/lib
LDADD = $(top_builddir)/lib/libhdfdump.a

hdfdump_SOURCES = hdf_dump_array.c hdf_print_info.c hdfdump.c hdfindex.c

### Makefile.am ends here
