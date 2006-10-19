
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
  OUTTYPE_FLOAT,
  OUTTYPE_TEXT,
  OUTTYPE_RAW
};

int *str2indexs (char *string, int *index);
int hdf_dump_array(void * var, nc_type data_type, int length, double multiply, 
		   enum t_output_type output_type, double addofset, 
		   double scale_factor, void *fill_value);
void *selection (int ncid, int varid,
                 const int **set, const int *sizes, 
		 int *number_of_point);

int hdf_print_attribute_info (int ncid, int varid,
                              const char *attribute_name, int attnum);
int hdf_print_sds_info(int ncid, int varid);

#endif /* #ifndef NDFINDEX_H */
