/*** numconv.h --- ?  -*- C -*- */

/*** Copyright (C) 2007 Ivan Shmakov */

/*** Code: */
#ifndef NUMCONV_H
#define NUMCONV_H

#include <stddef.h>             /* for size_t */
#include <stdint.h>

/** Simple coercion */

void nconv_double_from_int8_t   (double *dst, const int8_t *src,
                                 size_t size);
void nconv_double_from_int16_t  (double *dst, const int16_t *src,
                                 size_t size);
void nconv_double_from_int32_t  (double *dst, const int32_t *src,
                                 size_t size);
void nconv_double_from_int64_t  (double *dst, const int64_t *src,
                                 size_t size);

void nconv_double_from_uint8_t  (double *dst, const uint8_t *src,
                                 size_t size);
void nconv_double_from_uint16_t (double *dst, const uint16_t *src,
                                 size_t size);
void nconv_double_from_uint32_t (double *dst, const uint32_t *src,
                                 size_t size);
void nconv_double_from_uint64_t (double *dst, const uint64_t *src,
                                 size_t size);

void nconv_double_from_float    (double *dst, const float *src,
                                 size_t size);

void nconv_float_from_int8_t    (float *dst, const int8_t *src,
                                 size_t size);
void nconv_float_from_int16_t   (float *dst, const int16_t *src,
                                 size_t size);
void nconv_float_from_int32_t   (float *dst, const int32_t *src,
                                 size_t size);
void nconv_float_from_int64_t   (float *dst, const int64_t *src,
                                 size_t size);

void nconv_float_from_uint8_t   (float *dst, const uint8_t *src,
                                 size_t size);
void nconv_float_from_uint16_t  (float *dst, const uint16_t *src,
                                 size_t size);
void nconv_float_from_uint32_t  (float *dst, const uint32_t *src,
                                 size_t size);
void nconv_float_from_uint64_t  (float *dst, const uint64_t *src,
                                 size_t size);

void nconv_float_from_double    (float *dst, const double *src,
                                 size_t size);

/** Coercion, mapping a given value to NaN */

void nconv_nan_double_from_int8_t   (double *dst, const int8_t *src,
                                     size_t size,
                                     const int8_t *const map_to_nan);
void nconv_nan_double_from_int16_t  (double *dst, const int16_t *src,
                                     size_t size,
                                     const int16_t *const map_to_nan);
void nconv_nan_double_from_int32_t  (double *dst, const int32_t *src,
                                     size_t size,
                                     const int32_t *const map_to_nan);
void nconv_nan_double_from_int64_t  (double *dst, const int64_t *src,
                                     size_t size,
                                     const int64_t *const map_to_nan);

void nconv_nan_double_from_uint8_t  (double *dst, const uint8_t *src,
                                     size_t size,
                                     const uint8_t *const map_to_nan);
void nconv_nan_double_from_uint16_t (double *dst, const uint16_t *src,
                                     size_t size,
                                     const uint16_t *const map_to_nan);
void nconv_nan_double_from_uint32_t (double *dst, const uint32_t *src,
                                     size_t size,
                                     const uint32_t *const map_to_nan);
void nconv_nan_double_from_uint64_t (double *dst, const uint64_t *src,
                                     size_t size,
                                     const uint64_t *const map_to_nan);

void nconv_nan_double_from_float    (double *dst, const float *src,
                                     size_t size,
                                     const float *const map_to_nan);
void nconv_nan_double_from_double   (double *dst, const double *src,
                                     size_t size,
                                     const float *const map_to_nan);

void nconv_nan_float_from_int8_t    (float *dst, const int8_t *src,
                                     size_t size,
                                     const int8_t *const map_to_nan);
void nconv_nan_float_from_int16_t   (float *dst, const int16_t *src,
                                     size_t size,
                                     const int16_t *const map_to_nan);
void nconv_nan_float_from_int32_t   (float *dst, const int32_t *src,
                                     size_t size,
                                     const int32_t *const map_to_nan);
void nconv_nan_float_from_int64_t   (float *dst, const int64_t *src,
                                     size_t size,
                                     const int64_t *const map_to_nan);

void nconv_nan_float_from_uint8_t   (float *dst, const uint8_t *src,
                                     size_t size,
                                     const uint8_t *const map_to_nan);
void nconv_nan_float_from_uint16_t  (float *dst, const uint16_t *src,
                                     size_t size,
                                     const uint16_t *const map_to_nan);
void nconv_nan_float_from_uint32_t  (float *dst, const uint32_t *src,
                                     size_t size,
                                     const uint32_t *const map_to_nan);
void nconv_nan_float_from_uint64_t  (float *dst, const uint64_t *src,
                                     size_t size,
                                     const uint64_t *const map_to_nan);

void nconv_nan_float_from_double    (float *dst, const double *src,
                                     size_t size,
                                     const double *const map_to_nan);
void nconv_nan_float_from_float     (float *dst, const float *src,
                                     size_t size,
                                     const float *const map_to_nan);

#endif
/*** Emacs stuff */
/** Local variables: */
/** fill-column: 72 */
/** indent-tabs-mode: nil */
/** ispell-local-dictionary: "british" */
/** mode: outline-minor */
/** outline-regexp: "/[*][*][*]" */
/** End: */
/** LocalWords:   */
/*** numconv.h ends here */
