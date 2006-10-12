#define _ISOC99_SOURCE
#include "hdfdump.h"

#include "my_debug.h"

/*  OUTTYPE_DEFAULT,
  OUTTYPE_FLOAT,
  OUTTYPE_TEXT,
  OUTTYPE_RAW */

int
hdf_dump_array(void * var, nc_type data_type, int length, double multiply,
	       enum t_output_type output_type, double add_offset,
	       double scale_factor, void *fill_value)
{

  int i;
  float  *tmp;
  char   *var_char;
  short  *var_short;
  long   *var_long;
  float  *var_float;
  double *var_double;

  if(output_type == OUTTYPE_RAW){
    fwrite(var, nctypelen(data_type), length, stdout);
    return 0;
  }

  switch(data_type) {

  case NC_BYTE:
    var_char = (char *) var;
    switch(output_type){
    case OUTTYPE_TEXT:
      for(i = 0; i < length; i++) 
	if(fill_value != NULL && ! memcmp((void *) (var_char + i), fill_value, 1))
	  printf("NaN\n");
	else
	  printf ("%lf\n", (double)(multiply * (var_char[i] * scale_factor + add_offset)));
      break;
    case OUTTYPE_FLOAT:
      tmp = malloc(length * sizeof(float));
      for(i = 0; i < length; i++) 
	if(fill_value != NULL && ! memcmp((void *) (var_char + i), fill_value, 1)) 
	  tmp[i] = NAN;
	else
	  tmp[i] = (var_char[i] * scale_factor + add_offset) * multiply;
      fwrite(tmp, sizeof(float), length, stdout);
      free (tmp);
      break;
    default: 
      error(1, 0, "Invalid output type");
      return -1;
    }
    break;

  case NC_CHAR:
    switch(output_type){
    case OUTTYPE_TEXT:
      for(i = 0; i < length; i++) printf("%c", (char) (*((char *)var + i)));
      printf("\n");
      break;
    case OUTTYPE_FLOAT:
      error(0, 0, "Can't convert char to float");
      return -1;
    default: 
      error(1, 0, "Invalid output type");
      return -1;
    }
    break;

  case NC_SHORT:
    var_short = (short *) var;
    switch(output_type){
    case OUTTYPE_TEXT:
      for(i = 0; i < length; i++) 
	if(fill_value != NULL && ! memcmp((void *) (var_short + i), fill_value, 2))
	  printf("NaN\n");
	else{
	  printf ("%lf\n", (double)(multiply * (var_short[i] * scale_factor + add_offset)));
	}
      break;
    case OUTTYPE_FLOAT:
      tmp = malloc(length * sizeof(float));
      for(i = 0; i < length; i++) 
	if(fill_value != NULL && ! memcmp((void *) (var_short + i), fill_value, 2)) 
	  tmp[i] = NAN;
	else
	  tmp[i] = (float)(multiply * (var_short[i] * scale_factor + add_offset));
      fwrite(tmp, sizeof(float), length, stdout);
      free (tmp);
      break;
    default: 
      error(1, 0, "Invalid output type");
      return -1;
    }
    break;

  case NC_LONG:
    var_long = (long *) var;
    switch(output_type){
    case OUTTYPE_TEXT:
	for(i = 0; i < length; i++)
	  if(fill_value != NULL && ! memcmp((void *) (var_long + i), fill_value, 4))
	    printf("NaN\n");
	  else
	    printf ("%lf\n", (double)(multiply * (var_long[i] * scale_factor + add_offset)));
	break;
    case OUTTYPE_FLOAT:
      tmp = malloc(length * sizeof(float));
      for(i = 0; i < length; i++) 
	if(fill_value != NULL && ! memcmp((void *) (var_long + i), fill_value, 4)) 
	  tmp[i] = NAN;
	else
	  tmp[i] = (var_long[i] * scale_factor + add_offset) * multiply;
      fwrite(tmp, sizeof(float), length, stdout);
      free (tmp);
      break;
    default: 
      error(1, 0, "Invalid output type");
      return -1;
    }
    break;

  case NC_FLOAT:
    var_float = (float *) var;
    switch(output_type){
    case OUTTYPE_TEXT:
      for(i = 0; i < length; i++) 
	if(fill_value != NULL && ! memcmp((void *) (var_float + i), fill_value, 4))
	  printf("NaN\n");
	else
	  printf ("%lf\n", (double)(multiply * (var_float[i] * scale_factor + add_offset)));
      break;
    case OUTTYPE_FLOAT:
      tmp = malloc(length * sizeof(float));
      for(i = 0; i < length; i++) 
	if(fill_value != NULL && ! memcmp((void *) (var_float + i), fill_value, 4)) 
	  tmp[i] = NAN;
	else
	  tmp[i] = (var_float[i] * scale_factor + add_offset) * multiply;
	fwrite(tmp, sizeof(float), length, stdout);
	free (tmp);
      break;
    default: 
      error(1, 0, "Invalid output type");
      return -1;
    }
    break;

  case NC_DOUBLE:
    var_double = (double *) var;
    switch(output_type){
    case OUTTYPE_TEXT:
      for(i = 0; i < length; i++) 
	if(fill_value != NULL && ! memcmp((void *) (var_double + i), fill_value, 4))
	  printf("NaN\n");
	else
	  printf ("%lf\n", (double)(multiply * (var_double[i] * scale_factor + add_offset)));
      break;
    case OUTTYPE_FLOAT:
      tmp = malloc(length * sizeof(float));
      for(i = 0; i < length; i++) 
	if(fill_value != NULL && ! memcmp((void *) (var_double + i), fill_value, 1)) 
	  tmp[i] = NAN;
	else
	  tmp[i] = (var_double[i] * scale_factor + add_offset) * multiply;;
      fwrite(tmp, sizeof(float), length, stdout);
      free (tmp);
      break;
    default: 
      error(1, 0, "Invalid output type");
      return -1;
    }
  break;
  
  default:
    error(1, 0, "Invalid data type");
  }
  return 0;
}
