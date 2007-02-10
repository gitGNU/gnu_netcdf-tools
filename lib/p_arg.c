/*** p_arg.c --- Common parsing routines  -*- C -*- */

/*** Copyright (C) 2006 Ivan Shmakov */

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
