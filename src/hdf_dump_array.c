#define _ISOC99_SOURCE
#include "hdfdump.h"

/*  OUTTYPE_DEFAULT,
  OUTTYPE_FLOAT,
  OUTTYPE_TEXT,
  OUTTYPE_RAW */

int
hdf_dump_array (void *var, nc_type data_type, size_t length,
                const struct output_conversion *conv,
                FILE *fp)
{
  const enum t_output_type output_type = conv->output_type;
  const double
    coeff  = conv->coeffs[1],
    offset = conv->coeffs[0];
  void *const fill_value = conv->map_to_nan;
  int i;
  float  *tmp;
  unsigned char   *var_char;
  short  *var_short;
  long   *var_long;
  float  *var_float;
  double *var_double;

  if(output_type == OUTTYPE_RAW){
    fwrite (var, nctypelen (data_type), length, fp);
    return 0;
  }

  switch(data_type) {

  case NC_BYTE:
    var_char = (unsigned char *) var;
    switch(output_type){
    case OUTTYPE_TEXT:
      for(i = 0; i < length; i++) 
	if(fill_value != NULL && ! memcmp((void *) (var_char + i), fill_value, 1))
          fputs ("NaN\n", fp);
	else
          fprintf (fp, "%lf\n", (double)(coeff * var_char[i] + offset));
      break;
    case OUTTYPE_FLOAT:
      tmp = malloc(length * sizeof(float));
      for(i = 0; i < length; i++) 
	if(fill_value != NULL && ! memcmp((void *) (var_char + i), fill_value, 1)) 
	  tmp[i] = NAN;
	else
          tmp[i] = coeff * var_char[i] + offset;
      fwrite (tmp, sizeof (float), length, fp);
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
      for(i = 0; i < length; i++) fprintf (fp, "%c", ((char *)var)[i]);
      fputs ("\n", fp);
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
          fputs ("NaN\n", fp);
	else{
          fprintf (fp, "%lf\n",
                   (double)(coeff * var_short[i] + offset));
	}
      break;
    case OUTTYPE_FLOAT:
      tmp = malloc(length * sizeof(float));
      for(i = 0; i < length; i++) 
	if(fill_value != NULL && ! memcmp((void *) (var_short + i), fill_value, 2)) 
	  tmp[i] = NAN;
	else
          tmp[i] = (float)(coeff * var_short[i] + offset);
      fwrite (tmp, sizeof (float), length, fp);
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
          fputs ("NaN\n", fp);
	  else
          fprintf (fp, "%lf\n", (double)(coeff * var_long[i] + offset));
	break;
    case OUTTYPE_FLOAT:
      tmp = malloc(length * sizeof(float));
      for(i = 0; i < length; i++) 
	if(fill_value != NULL && ! memcmp((void *) (var_long + i), fill_value, 4)) 
	  tmp[i] = NAN;
	else
          tmp[i] = coeff * var_long[i] + offset;
      fwrite (tmp, sizeof (float), length, fp);
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
          fputs ("NaN\n", fp);
	else
          fprintf (fp, "%lf\n",
                   (double)(coeff * var_float[i] + offset));
      break;
    case OUTTYPE_FLOAT:
      tmp = malloc(length * sizeof(float));
      for(i = 0; i < length; i++) 
	if(fill_value != NULL && ! memcmp((void *) (var_float + i), fill_value, 4)) 
	  tmp[i] = NAN;
	else
          tmp[i] = coeff * var_float[i] + offset;
      fwrite (tmp, sizeof (float), length, fp);
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
          fputs ("NaN\n", fp);
	else
          fprintf (fp, "%lf\n", (double)(coeff * var_double[i] + offset));
      break;
    case OUTTYPE_FLOAT:
      tmp = malloc(length * sizeof(float));
      for(i = 0; i < length; i++) 
	if(fill_value != NULL && ! memcmp((void *) (var_double + i), fill_value, 1)) 
	  tmp[i] = NAN;
	else
          tmp[i] = coeff * var_double[i] + offset;;
      fwrite (tmp, sizeof (float), length, fp);
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
