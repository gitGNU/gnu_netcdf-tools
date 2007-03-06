/*** useutil.h --- Useful utility functions  -*- C -*- */

/*** Copyright (C) 2007 Ivan Shmakov */

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
