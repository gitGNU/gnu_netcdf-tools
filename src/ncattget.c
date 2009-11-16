/*** ncattget.c --- A tiny ncattget () wrapper  -*- C -*- */

/*** Ivan Shmakov, 2009 */
/** This code is in the public domain */

/*** Code: */
#define _GNU_SOURCE
#include <assert.h>
#include <errno.h>		/* for program_invocation_short_name */
#include <error.h>
#include <stdio.h>
#include <stdlib.h>

#include <netcdf.h>

int
main (int argc, const char *argv[])
{
  if (-1 + argc != 3) {
    error (1, 0, "Usage: %s FILE VARIABLE-NAME ATTRIBUTE-NAME",
           program_invocation_short_name);
  }

  const char
    *filename = argv[1],
    *varn     = argv[2],
    *attn     = argv[3];

  int ds;
  {
    ds = ncopen (filename, NC_NOWRITE);
    assert (! (ds < 0));
  }

  int var;
  if (varn[0] != '\0') {
    var = ncvarid (ds, varn);
    assert (! (var < 0));
  } else {
    var = NC_GLOBAL;
  }

  size_t len, elt_sz;
  int elts;
  {
    int r;
    nc_type typ;
    r = ncattinq (ds, var, attn, &typ, &elts);
    /* ??? assert (r == NC_NOERR); */

    elt_sz = nctypelen (typ);
    assert (elt_sz > 0);
    len = elts * elt_sz;
  }

  char buf[len];
  {
    int r;
    r = ncattget (ds, var, attn, buf);
    /* ??? assert (r == NC_NOERR); */
  }

  {
    size_t r;
    r = fwrite ((void *)buf, elt_sz, elts, stdout);
    assert (r == elts);
  }

  /* . */
  return 0;
}

/*** ncattget.c ends here */
