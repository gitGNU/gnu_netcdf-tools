#define _ISOC99_SOURCE
#include <assert.h>

#include "hdfdump.h"

#include "numconv.h"

static void
coerce (void *dst, const void *src, size_t size,
        const struct output_conversion *conv,
        nc_type input_type)
{
  const enum t_output_type otyp = conv->output_type;
  void (*fn) (void *, const void *, size_t, const void *const);

  /* NB: handled separately */
  assert (otyp != OUTTYPE_DEFAULT
          && otyp != OUTTYPE_TEXT
          && otyp != OUTTYPE_RAW);

  switch (otyp) {
  case OUTTYPE_DOUBLE:
    switch (input_type) {
    case NC_BYTE:   fn = nconv_nan_double_from_uint8_t; break;
    case NC_SHORT:  fn = nconv_nan_double_from_int16_t; break;
    case NC_LONG:   fn = nconv_nan_double_from_int32_t; break;
    case NC_FLOAT:  fn = nconv_nan_double_from_float;   break;
    case NC_DOUBLE: fn = nconv_nan_double_from_double;  break;
    default:
      error (1, 0, "%d: unhandled input type in `%s'",
             input_type, __FUNCTION__);
      break;
    }
    break;
  case OUTTYPE_FLOAT:
    switch (input_type) {
    case NC_BYTE:   fn = nconv_nan_float_from_uint8_t;  break;
    case NC_SHORT:  fn = nconv_nan_float_from_int16_t;  break;
    case NC_LONG:   fn = nconv_nan_float_from_int32_t;  break;
    case NC_FLOAT:  fn = nconv_nan_float_from_float;    break;
    case NC_DOUBLE: fn = nconv_nan_float_from_double;   break;
    default:
      error (1, 0, "%d: unhandled input type in `%s'",
             input_type, __FUNCTION__);
      break;
    }
    break;
  default:
    error (1, 0, "%d: unhandled output type in `%s'",
           otyp, __FUNCTION__);
    break;
  }

  fn (dst, src, size, conv->map_to_nan);
}

static void
linear_double (double *ary, size_t size,
               const struct output_conversion *conv)
{
  const double
    k = conv->coeffs[1],
    b = conv->coeffs[0];
  size_t rest;
  double *p;

  for (rest = size, p = ary; rest > 0; rest--, p++) {
    if (! isnan (*p)) {
      *p = k * (*p) + b;
    }
  }
}

static void
linear_float (float *ary, size_t size,
              const struct output_conversion *conv)
{
  const double
    k = conv->coeffs[1],
    b = conv->coeffs[0];
  size_t rest;
  float *p;

  for (rest = size, p = ary; rest > 0; rest--, p++) {
    if (! isnan (*p)) {
      *p = k * (*p) + b;
    }
  }
}

static int
fprint_conv_ary (const void *ary, size_t size,
                 const struct output_conversion *conv,
                 nc_type input_type, FILE *fp)
{
  const double
    coeff  = conv->coeffs[1],
    offset = conv->coeffs[0];
  void *const map_to_nan = conv->map_to_nan;

  assert (input_type != NC_CHAR);

#define COMMON_BLOCK \
      if (map_to_nan == 0) { \
        for (rest = size, p = ary; rest > 0; rest--, p++) { \
          fprintf (fp, "%g\n", (double)(coeff * (*p) + offset)); \
        } \
      } else { \
        for (rest = size, p = ary; rest > 0; rest--, p++) { \
          if (memcmp (p, map_to_nan, sizeof (*p)) == 0) { \
            fputs ("NaN\n", fp); \
          } else { \
            fprintf (fp, "%g\n", (double)(coeff * (*p) + offset)); \
          } \
        } \
      }

  switch (input_type) {
  case NC_BYTE:
    {
      size_t rest;
      const unsigned char *p;
#if 1
      COMMON_BLOCK ;
#else
      if (map_to_nan == 0) {
        for (rest = size, p = ary; rest > 0; rest--, p++) {
          fprintf (fp, "%g\n", (double)(coeff * (*p) + offset));
        }
      } else {
        for (rest = size, p = ary; rest > 0; rest--, p++) {
          if (memcmp (p, map_to_nan, sizeof (*p)) == 0) {
            fputs ("NaN\n", fp);
          } else {
            fprintf (fp, "%g\n", (double)(coeff * (*p) + offset));
          }
        }
      }
#endif
    }
    break;
  case NC_SHORT:
    {
      size_t rest;
      const int16_t *p;
      COMMON_BLOCK ;
    }
    break;
  case NC_LONG:
    {
      size_t rest;
      const uint32_t *p;
      COMMON_BLOCK ;
    }
    break;
  case NC_FLOAT:
    {
      size_t rest;
      const float *p;
      COMMON_BLOCK ;
    }
    break;
  case NC_DOUBLE:
    {
      size_t rest;
      const double *p;
      COMMON_BLOCK ;
    }
    break;
  default:
    error (1, 0, "%d: unhandled input type in `%s'",
           input_type, __FUNCTION__);
    break;
  }

#undef COMMON_BLOCK

  return 0;
}

int
hdf_dump_array (void *var, nc_type data_type, size_t length,
                const struct output_conversion *conv,
                FILE *fp)
{
  const enum t_output_type output_type = conv->output_type;

  assert (output_type != OUTTYPE_DEFAULT);

  if (output_type == OUTTYPE_RAW
      || (output_type == OUTTYPE_TEXT && data_type == NC_CHAR)) {
    fwrite (var, nctypelen (data_type), length, fp);
  } else if (output_type == OUTTYPE_TEXT) {
    fprint_conv_ary (var, length, conv, data_type, fp);
  } else if (data_type == NC_CHAR) {
    error (1, 0, "NC_CHAR could be only dumped as text or raw");
  } else {
    switch (output_type) {
    case OUTTYPE_DOUBLE:
      {
        double a[length];
        coerce (a, var, length, conv, data_type);
        linear_double (a, length, conv);
        fwrite (a, sizeof (*a), length, fp);
      }
      break;
    case OUTTYPE_FLOAT:
      {
        float a[length];
        coerce (a, var, length, conv, data_type);
        linear_float (a, length, conv);
        fwrite (a, sizeof (*a), length, fp);
      }
      break;
    default:
      error (1, 0, "%d: unhandled output type in `%s'",
             output_type, __FUNCTION__);
      break;
    }
  }

  return 0;
}
