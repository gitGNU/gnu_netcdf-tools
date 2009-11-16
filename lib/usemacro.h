/*** usemacro.h --- Useful Macros  -*- C -*- */

/*** Copyright (C) 2006 Ivan Shmakov */

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
#ifndef USEMACRO_H
#define USEMACRO_H

/** arithmetic and logic */
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define BOUND(v, min, max) (MIN (MAX ((min), (v)), (max)))

/** memory allocation */
#define MALLOC_VAR(x) \
    (((x) = (typeof ((x)))malloc             (sizeof (*(x)))))
#define MALLOC_ARY(x, y) \
    (((x) = (typeof ((x)))malloc       ((y) * sizeof (*(x)))))
#define REALLOC_ARY(x, y) \
    (((x) = (typeof ((x)))realloc ((x), (y) * sizeof (*(x)))))

/** memory operations */
#define COPY_VAR(x, z) \
    ((typeof ((x)))memcpy ((x), (z),       sizeof (*(x))))
#define COPY_ARY(x, z, y) \
    ((typeof ((x)))memcpy ((x), (z), (y) * sizeof (*(x))))

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
/*** usemacro.h ends here */
