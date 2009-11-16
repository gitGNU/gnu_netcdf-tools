/*** ncattput.c --- A tiny ncattput () wrapper  -*- C -*- */

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
    ds = ncopen (filename, NC_WRITE);
    assert (! (ds < 0));
  }

  int var;
  if (varn[0] != '\0') {
    var = ncvarid (ds, varn);
    assert (! (var < 0));
  } else {
    var = NC_GLOBAL;
  }

  const nc_type atype = NC_CHAR;
  assert (nctypelen (atype) == 1);

  char *buf = 0;
  size_t elts = 0, buf_sz = 0;
  {
    FILE *fp = stdin;
    char *bp = buf;
    while (! feof (fp)) {
      if (buf_sz - elts <= 0) {
	const size_t new_sz = (buf_sz << 1) + 3;
	char *new = realloc (buf, new_sz);
	assert (new != 0);
	bp  = new + (bp - buf);
	buf = new;
	buf_sz = new_sz;
      }

      size_t r;
      r = fread (bp, 1, buf_sz - elts, fp);
      assert (r > 0);
      elts += r;
      bp += r;
    }
  }

  {
    int r;
    r = ncredef (ds);
    /* ??? assert (r ???); */
  }

  {
    int r;
    r = ncattput (ds, var, attn, atype, elts, (void *)buf);
    /* ??? assert (r == NC_NOERR); */
  }

  {
    int r;
    r = ncclose (ds);
    /* ??? assert (r ???); */
  }

  /* . */
  return 0;
}

/*** ncattput.c ends here */
