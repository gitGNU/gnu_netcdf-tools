
#ifndef HDFDUMP_H
#define HDFDUMP_H

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

int *str2indexs (char *string, int *index);
void *selection (int ncid, int varid,
                 const int **set, const int *sizes, 
		 int *number_of_point);

int hdf_dump_array (void *var, nc_type data_type, size_t length,
                    const struct output_conversion *conv,
                    FILE *fp);

int hdf_print_attribute_info (int ncid, int varid,
                              const char *attribute_name, int attnum);
int hdf_print_sds_info(int ncid, int varid);

#endif /* #ifndef NDFINDEX_H */
