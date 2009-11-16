/*** ncget.c --- Common declarations for ncget  -*- C -*- */

/*** Copyright (C) 2007, 2009 Ivan Shmakov */
/*** Copyright (C) 2006 Anton Reznikov */

/** This program is free software; you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation; either version 2 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful, but
 ** WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 ** General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program; if not, write to the Free Software
 ** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 ** 02110-1301 USA
 */

/*** Code: */
#ifndef NCGET_H
#define NCGET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netcdf.h>
#include <ctype.h>
#include <math.h>

#include <error.h>
#include <errno.h>
#include <unistd.h>


enum t_output_type {
  OUTTYPE_DEFAULT,
  OUTTYPE_DOUBLE,
  OUTTYPE_FLOAT,
  OUTTYPE_TEXT,
  OUTTYPE_RAW
};

struct output_conversion {
  enum t_output_type output_type;
  double coeffs[2];
  void *map_to_nan;
};

int *ncsel_strtoi (char *string, int *index);
void *ncsel (int ncid, int varid,
             const int **set, const int *sizes, 
             int *number_of_point);

int dump_array (void *var, nc_type data_type, size_t length,
                const struct output_conversion *conv,
                FILE *fp);

int print_nc_attribute_info (int ncid, int varid,
                             const char *attribute_name, int attnum);
int print_nc_sds_info (int ncid, int varid);

#endif

/*** ncget.c ends here */
