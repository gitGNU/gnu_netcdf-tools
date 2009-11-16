### Makefile.am  -*- Makefile -*-

bin_PROGRAMS =
if HAVE_LIBNETCDF
bin_PROGRAMS += ncget
endif
if HAVE_LIBHDF4
bin_PROGRAMS += ncget-hdf
endif

AM_CFLAGS = -Wall
AM_CPPFLAGS = -I$(top_builddir)/lib -I$(top_srcdir)/lib
LDADD = $(top_builddir)/lib/libhdfdump.a

LIBS_NETCDF = $(LIBS) $(LIBS_NETCDF_EXTRA)
LIBS_HDF4   = $(LIBS) $(LIBS_HDF4_EXTRA)

ncget_SOURCES_1 = hdf_dump_array.c hdf_print_info.c hdfdump.c hdfindex.c

## FIXME: eliminate a hard-coded path
CPPFLAGS_HDF4 = -I/usr/include/hdf $(CPPFLAGS)

ncget_SOURCES = $(ncget_SOURCES_1)
ncget_LDADD = $(LIBS_NETCDF) $(LDADD)

ncget_hdf_SOURCES = $(ncget_SOURCES_1)
ncget_hdf_LDADD = $(LIBS_HDF4) $(LDADD)
ncget_hdf_CPPFLAGS = $(AM_CPPFLAGS) $(CPPFLAGS_HDF4)

### Makefile.am ends here
