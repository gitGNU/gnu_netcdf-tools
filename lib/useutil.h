/*** useutil.h --- Useful utility functions  -*- C -*- */

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
#ifndef USEUTIL_H
#define USEUTIL_H

#include <stdio.h>		/* for FILE */

int ensure_enough_space (void **ptr, size_t *allocptr,
			 size_t size, size_t wanted);

/** Vectors of Strings */
struct strings {
  size_t size, alloc;
  const char **s;
};

int strings_append (struct strings *vec, const char **s, size_t count);
void strings_clear (struct strings *vec);

/** Usual file I/O */
FILE *open_file (const char *arg, int input_p);
void close_file (FILE *fp);

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
/*** useutil.h ends here */
