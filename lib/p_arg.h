/*** p_arg.h --- Common parsing routines  -*- C -*- */

/*** Copyright (C) 2006 Ivan Shmakov */

/*** Code: */
#ifndef P_ARG_H
#define P_ARG_H

/** skipping whitespace characters */
const char *p_arg_skipspace (const char *s);

/** matching string values */
int p_arg_string (const char *s, const char **tokens, int exact_p);

/** parsing numbers */
int p_arg_double (const char *s, double *vp);
int p_arg_long   (const char *s, long   *vp);

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
/*** p_arg.h ends here */
