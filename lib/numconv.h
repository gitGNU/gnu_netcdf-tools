/*** numconv.h --- ?  -*- C -*- */

/*** Copyright (C) 2007 Ivan Shmakov */

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
