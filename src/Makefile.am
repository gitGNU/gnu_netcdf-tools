### Makefile.am  -*- Makefile-Automake -*-

bin_PROGRAMS =
if HAVE_LIBNETCDF
bin_PROGRAMS += ncattget ncattput
bin_PROGRAMS += ncget
endif
if HAVE_LIBHDF4
bin_PROGRAMS += ncattget-hdf ncattput-hdf
bin_PROGRAMS += ncget-hdf
endif

AM_CFLAGS = -Wall
AM_CPPFLAGS = -I$(top_builddir)/lib -I$(top_srcdir)/lib

LIBS_NCTOOLS_EXTRA = $(top_builddir)/lib/libhdfdump.a

LIBS_NETCDF = $(LIBS) $(LIBS_NETCDF_EXTRA)
LIBS_HDF4   = $(LIBS) $(LIBS_HDF4_EXTRA)

## FIXME: eliminate a hard-coded path
CPPFLAGS_HDF4 = -I/usr/include/hdf $(CPPFLAGS)

ncattget_SOURCES = ncattget.c
ncattput_SOURCES = ncattput.c
ncattget_LDADD = $(LIBS_NETCDF)
ncattput_LDADD = $(LIBS_NETCDF)

ncattget_hdf_SOURCES = ncattget.c
ncattput_hdf_SOURCES = ncattput.c
ncattget_hdf_LDADD = $(LIBS_HDF4)
ncattput_hdf_LDADD = $(LIBS_HDF4)
ncattget_hdf_CPPFLAGS = $(CPPFLAGS_HDF4)
ncattput_hdf_CPPFLAGS = $(CPPFLAGS_HDF4)

ncget_SOURCES_1 = dump_array.c print_nc_info.c ncget.c ncsel.c

ncget_SOURCES = $(ncget_SOURCES_1)
ncget_LDADD = $(LIBS_NCTOOLS_EXTRA) $(LIBS_NETCDF) $(LDADD)

ncget_hdf_SOURCES = $(ncget_SOURCES_1)
ncget_hdf_LDADD = $(LIBS_NCTOOLS_EXTRA) $(LIBS_HDF4) $(LDADD)
ncget_hdf_CPPFLAGS = $(AM_CPPFLAGS) $(CPPFLAGS_HDF4)

### Makefile.am ends here
