/*** numconv.c --- C Numeric Types Conversions  -*- C -*- */
#define _GNU_SOURCE
#define _ISOC99_SOURCE

/*** Copyright (C) 2007 Ivan Shmakov */

/*** Code: */
#include <math.h>               /* for isnan (), NAN */
#include <stddef.h>             /* for size_t */
#include <stdint.h>

#define NUM_COERCE(fn, to_type, from_type) \
    void \
    fn (to_type *dst, const from_type *src, size_t size) { \
      size_t rest; \
      to_type *dp; \
      const from_type *sp; \
      for (rest = size, dp = dst, sp = src; \
           rest > 0; \
           rest--, *(dp++) = *(sp++)) \
        ; \
    }

#define NUM_COERCE_NAN_FROM(fn, to_type, from_type) \
    void \
    fn (to_type *dst, const from_type *src, size_t size, \
        const from_type *const map_to_nan) { \
      size_t rest; \
      to_type *dp; \
      const from_type *sp; \
      for (rest = size, dp = dst, sp = src; \
           rest > 0; \
           rest--, dp++, sp++) { \
        *dp = ((map_to_nan != 0 \
                && memcmp (sp, map_to_nan, sizeof (*sp)) == 0) ? NAN \
               : *sp); \
      } \
    }

#define NUM_COERCE_NAN(fn, to_type, from_type) \
    void \
    fn (to_type *dst, const from_type *src, size_t size, \
        const from_type *const map_to_nan, \
        const to_type *const map_from_nan) { \
      size_t rest; \
      to_type *dp; \
      const from_type *sp; \
      for (rest = size, dp = dst, sp = src; \
           rest > 0; \
           rest--, dp++, sp++) { \
        *dp = ((map_to_nan != 0 \
                && memcmp (sp, map_to_nan, sizeof (*sp)) == 0) ? NAN \
               : map_from_nan != 0 && isnan (*sp) ? *map_from_nan \
               : *sp); \
      } \
    }

/** Simple coercion */
NUM_COERCE (nconv_double_from_int8_t,   double, int8_t)
NUM_COERCE (nconv_double_from_int16_t,  double, int16_t)
NUM_COERCE (nconv_double_from_int32_t,  double, int32_t)
NUM_COERCE (nconv_double_from_int64_t,  double, int64_t)

NUM_COERCE (nconv_double_from_uint8_t,  double, uint8_t)
NUM_COERCE (nconv_double_from_uint16_t, double, uint16_t)
NUM_COERCE (nconv_double_from_uint32_t, double, uint32_t)
NUM_COERCE (nconv_double_from_uint64_t, double, uint64_t)

NUM_COERCE (nconv_double_from_float,    double, float)

NUM_COERCE (nconv_float_from_int8_t,    float, int8_t)
NUM_COERCE (nconv_float_from_int16_t,   float, int16_t)
NUM_COERCE (nconv_float_from_int32_t,   float, int32_t)
NUM_COERCE (nconv_float_from_int64_t,   float, int64_t)

NUM_COERCE (nconv_float_from_uint8_t,   float, uint8_t)
NUM_COERCE (nconv_float_from_uint16_t,  float, uint16_t)
NUM_COERCE (nconv_float_from_uint32_t,  float, uint32_t)
NUM_COERCE (nconv_float_from_uint64_t,  float, uint64_t)

NUM_COERCE (nconv_float_from_double,    float, double)

/** Coercion, mapping a given value to NaN */

NUM_COERCE_NAN_FROM (nconv_nan_double_from_int8_t,   double, int8_t)
NUM_COERCE_NAN_FROM (nconv_nan_double_from_int16_t,  double, int16_t)
NUM_COERCE_NAN_FROM (nconv_nan_double_from_int32_t,  double, int32_t)
NUM_COERCE_NAN_FROM (nconv_nan_double_from_int64_t,  double, int64_t)

NUM_COERCE_NAN_FROM (nconv_nan_double_from_uint8_t,  double, uint8_t)
NUM_COERCE_NAN_FROM (nconv_nan_double_from_uint16_t, double, uint16_t)
NUM_COERCE_NAN_FROM (nconv_nan_double_from_uint32_t, double, uint32_t)
NUM_COERCE_NAN_FROM (nconv_nan_double_from_uint64_t, double, uint64_t)

NUM_COERCE_NAN_FROM (nconv_nan_double_from_float,    double, float)
NUM_COERCE_NAN_FROM (nconv_nan_double_from_double,   double, double)

NUM_COERCE_NAN_FROM (nconv_nan_float_from_int8_t,    float,  int8_t)
NUM_COERCE_NAN_FROM (nconv_nan_float_from_int16_t,   float,  int16_t)
NUM_COERCE_NAN_FROM (nconv_nan_float_from_int32_t,   float,  int32_t)
NUM_COERCE_NAN_FROM (nconv_nan_float_from_int64_t,   float,  int64_t)

NUM_COERCE_NAN_FROM (nconv_nan_float_from_uint8_t,   float,  uint8_t)
NUM_COERCE_NAN_FROM (nconv_nan_float_from_uint16_t,  float,  uint16_t)
NUM_COERCE_NAN_FROM (nconv_nan_float_from_uint32_t,  float,  uint32_t)
NUM_COERCE_NAN_FROM (nconv_nan_float_from_uint64_t,  float,  uint64_t)

NUM_COERCE_NAN_FROM (nconv_nan_float_from_float,     float,  float)
NUM_COERCE_NAN_FROM (nconv_nan_float_from_double,    float,  double)

/*** Emacs stuff */
/** Local variables: */
/** fill-column: 72 */
/** indent-tabs-mode: nil */
/** ispell-local-dictionary: "british" */
/** mode: outline-minor */
/** outline-regexp: "/[*][*][*]" */
/** End: */
/** LocalWords:   */
/*** numconv.c ends here */
