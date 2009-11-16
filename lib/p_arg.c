/*** p_arg.c --- Common parsing routines  -*- C -*- */

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

#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

const char *
p_arg_skipspace (const char *s)
{
  if (s == 0) return 0;         /* . */
  while (isspace (*s)) s++;
  /* . */
  return s;
}

int
p_arg_string (const char *s, const char **tokens, int exact_p)
{
  const char **t;
  const size_t sz = exact_p ? 0 : strlen (s);
  int i;

  /* check if `s' is empty */
  if (*s == '\0') {
    /* . */
    return -1;
  }

  for (t = tokens, i = -1; *t != 0; t++)
    if (sz ? ! strncmp (s, *t, sz) : ! strcmp (s, *t)) {
      if (! sz) {
        /* . */
        return t - tokens;
      }
      if (i >= 0) {
        /* . */
        return -1;
      }
      i = t - tokens;
    }

  /* . */
  return i;
}

int
p_arg_double (const char *s, double *vp)
{
  char *t;
  double v;

  if ((v = strtod (s, &t)),
      t == s || *t != '\0') {
    /* . */
    return -1;
  }
  if (vp != 0) *vp = v;

  /* . */
  return 0;
}

int
p_arg_long (const char *s, long *vp)
{
  char *t;
  long v;

  if ((v = strtol (s, &t, 0)),
      t == s || *t != '\0') {
    /* . */
    return -1;
  }
  if (vp != 0) *vp = v;

  /* . */
  return 0;
}

/*** Emacs stuff */
/** Local variables: */
/** fill-column: 72 */
/** indent-tabs-mode: nil */
/** ispell-local-dictionary: "british" */
/** mode: outline-minor */
/** outline-regexp: "/[*][*][*]" */
/** End: */
/** LocalWords:   */
/*** p_arg.c ends here */
