/*** ncget.c --- The ncget tool main ()  -*- C -*- */
#define _GNU_SOURCE
#define _ISOC99_SOURCE

/*** Copyright (C) 2007, 2009 Ivan Shmakov */
/*** Copyright (C) 2006 Anton Reznikov */

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
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <argp.h>

#include "ncget.h"
#include "p_arg.h"
#include "useutil.h"

/* FIXME: use gettext */
#if 1
#define  _(s) (s)
#define N_(s) (s)
#endif

const char *argp_program_version = PACKAGE_STRING;
const char *argp_program_bug_address = PACKAGE_BUGREPORT;

/* Program documentation. */
static char doc[] = "Dump an SDS or an attribute of the HDF file";
/* A description of the arguments we accept. */
static char args_doc[] = ("[OPTION] FILE SDS\n"
			  "[OPTION] FILE SDS:ATTRIBUTE");

/* Useful macros */
#define CASS(x, y) ((x) = (typeof (x))(y))
#define MALLOC_VAR(x)     (CASS ((x), malloc             (sizeof (*(x)))))
#define MALLOC_ARY(x, y)  (CASS ((x), malloc       ((y) * sizeof (*(x)))))
#define CALLOC_ARY(x, y)  (CASS ((x), calloc       ((y),  sizeof (*(x)))))
#define REALLOC_ARY(x, y) (CASS ((x), realloc ((x), (y) * sizeof (*(x)))))

/* Keys for options without short-options. */
/* ---- */

enum opts {
  opt_offset = 256,
  opt_double,
  opt_max
};

/* The options we understand. */

static struct argp_option options[] = {
  { 0, 0, 0, 0, "output format selection"},
  { "float32",  'f', NULL, 0, "float32 format" },
  { "double",   opt_double, NULL, 0, N_("double format") },
  { "text",     'T', NULL, 0, "text format (default for attributes)" },
  { "raw",      'R', NULL, 0, "raw data (default for SDSes), `-m' is ignored" },
  { 0, 0, 0, 0, "miscellaneous" },
  { "multiply", 'm', "MULTIPLIER", 0, "multiply each NAO element by the value given" },
  { "override-addoffset", 'a', "ADDOFFSET", 0, "Override addoffset given by HDFfile"
    "or define if it is undeclaed"},
  { "override-scalefactor", 's', "SCALEFACTOR", 0, "Override scalefactor given by HDFfile"
    "or define if it is undeclaed"},
  { "shape",    'S', NULL, 0, "print the SDS (or attribute) shape instead, in text format" },
  { "info",     'i', NULL, 0, "print the info about SDS (or attribute) in text format" },
  { "output",           'o', "FILE", 0,
    N_("output the result to this file instead of stdout") },
  {0}
};

struct arguments {
  char *input_file;
  char *sds_name;
  char *attribute_name;
  char *indexs;
  enum t_output_type output_type;
  double multiply;
  double add_offset;
  double scale_factor;
  int  shape;
  int info;
  const char *output_file;
};

/* Parse a single option. */
static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
  /* Get the `input' argument from `argp_parse', which we
     know is a pointer to our arguments structure. */
  struct arguments *args = state->input;
  char *tmp;

  switch (key) {
  case opt_double:
    args->output_type = OUTTYPE_DOUBLE;
    break;

  case 'f':
    args->output_type = OUTTYPE_FLOAT;
    break;

  case 'T':
    args->output_type = OUTTYPE_TEXT;
    break;

  case 'R':
    args->output_type = OUTTYPE_RAW;
    break;
    
  case 'S':
    args->shape = 1;
    break;

  case 'i':
    args->info = 1;
    break;

  case 'm':
    if (p_arg_double (arg, &args->multiply)) {
      argp_error (state, N_("%s: invalid multiplier,"
                            " should be a floating point number"),
                  arg);
      /* . */
      return EINVAL;
    }
    break;
  case 'a':
    if (p_arg_double (arg, &args->add_offset)) {
      argp_error (state, N_("%s: invalid offset to add,"
                            " should be a floating point number"),
                  arg);
      /* . */
      return EINVAL;
    }
    break;
  case 's':
    if (p_arg_double (arg, &args->scale_factor)) {
      argp_error (state, N_("%s: invalid scale,"
                            " should be a floating point number"),
                  arg);
      /* . */
      return EINVAL;
    }
    break;

  case ARGP_KEY_ARG:
    if(args->input_file == NULL){
      args->input_file = strdup(arg);
    }
    else if(args->sds_name == NULL && args->attribute_name == NULL){
      tmp = strchr(arg, ':');
      if(tmp == NULL){
	args->sds_name = strdup(arg);
      }
      else {
	args->attribute_name = strdup(tmp + 1);
	if(tmp == arg){
	  args->sds_name = NULL;
	}
	else{ 
	  args->sds_name = malloc((tmp - arg + 1) * sizeof(char));
	  strncpy(args->sds_name, arg, tmp - arg);
	  args->sds_name[tmp - arg] = '\0';
	}
      }
    } else if(args->indexs == NULL){
      args->indexs = arg;
    } else {
      argp_error (state, "too many non-option arguments given");
      return EINVAL;
    }
    break;

  case 'o':
    args->output_file = arg;
    break;

  case ARGP_KEY_END:
    if (args->input_file == NULL) {
      argp_error (state, "no file name given");
      return EINVAL;
    } else if (args->attribute_name == NULL
               && args->sds_name == NULL) {
      argp_error (state, "no SDS name given");
      return EINVAL;
    }
    break;

  default:
    return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc };


int main (int argc, char *argv[])
{
  struct arguments arguments;
  int ncid;
  int i;
  FILE *output;
  
  /* Default values.                  */
  arguments.input_file     = NULL;
  arguments.sds_name       = NULL;
  arguments.attribute_name = NULL;
  arguments.indexs         = NULL;
  arguments.output_type    = OUTTYPE_DEFAULT;
  arguments.multiply       = 1;
  arguments.add_offset      = NAN;
  arguments.scale_factor    = NAN;
  arguments.shape          = 0;
  arguments.info           = 0;
  arguments.output_file    = "-";
  /* -------------------------------- */

  /* parsing command line arguments   */
  argp_parse (&argp, argc, argv, 0, 0, &arguments);
  /* -------------------------------- */

  /* Dump values.                     */
  /*   dumps(arguments.input_file); */
  /*   dumps(arguments.sds_name); */
  /*   dumps(arguments.attribute_name); */
  /*   dumps(arguments.indexs); */
  /*   dumpi(arguments.output_type); */
  /*   dumpf(arguments.multiply); */
  /*   dumpf(arguments.add_offset); */
  /*   dumpf(arguments.scale_factor); */
  /*   dumpi(arguments.shape); */
  /* ---------------------------------*/

  ncid = ncopen (arguments.input_file, NC_NOWRITE);
  if (ncid < 0) {
    error (1, 0, "%s: Failed to open",
           arguments.input_file);
  }

  /* open the output file */
  if ((output = open_file (arguments.output_file, 0)) == 0) {
    error (1, errno, "%s", arguments.output_file);
  }

  if (arguments.attribute_name != NULL) {
    const char
      *sds_name = arguments.sds_name,
      *attribute_name = arguments.attribute_name;
    int varid;
    nc_type data_type;
    int data_len;

    if(arguments.output_type == OUTTYPE_DEFAULT) 
      arguments.output_type = OUTTYPE_TEXT;
    
    if (arguments.sds_name == NULL) {
      varid = NC_GLOBAL;
    } else if ((varid = ncvarid (ncid, sds_name)) < 0) {
      error (1, 0, "%s: No such SDS in file", sds_name);
    }
    
    ncattinq (ncid, varid, attribute_name, &data_type, &data_len);
    if(arguments.shape)
      printf("%d\n", data_len);
    else if(arguments.info) {
      print_nc_attribute_info (ncid, varid, attribute_name, 0);
    } else {
      void *data;
      int elt_sz;
      const struct output_conversion conv = {
        .output_type = arguments.output_type,
        .coeffs = { 0, arguments.multiply },
        .map_to_nan = 0
      };

      if ((elt_sz = nctypelen (data_type)) == -1) {
        error (1, 0, "%d: Unknown HDF data type", (int)data_type);
      }
      /* allocate memory */
      if ((data = malloc (elt_sz * data_len)) == 0) {
        error (1, errno, "Failed to allocate memory");
      }
      ncattget (ncid, varid, attribute_name, data);
      dump_array (data, data_type, data_len, &conv, output);
    }
  } else {
    const char
      *sds_name = arguments.sds_name;
    void *data, *fill_value;
    int varid;
    nc_type data_type;
    int ndims, dimids[MAX_VAR_DIMS], natts;
    int data_len;

    varid = ncvarid (ncid, sds_name);
    ncvarinq (ncid, varid, sds_name,
              &data_type, &ndims, dimids, &natts);

    if(arguments.shape){
      long dim;
      ncdiminq (ncid, dimids[0], (char *)0, &dim);
      printf ("%ld", dim);
      for (i = 1; i < ndims; i++){
	ncdiminq (ncid, dimids[i], (char *) 0 , &dim);
	printf (" %ld", dim);
      }
      printf("\n");
    } else if(arguments.info){
      print_nc_sds_info(ncid, varid);
    } else {
      char *ix_p;
      int **indexs, *indexs_dim;
      double add_offset, scale_factor;

      if(arguments.output_type == OUTTYPE_DEFAULT) 
	arguments.output_type = OUTTYPE_RAW;

      /* parsing of indexs */

      /* FIXME: check for failures */
      indexs = calloc(ndims, sizeof(int *));
      indexs_dim = calloc(ndims, sizeof(int));

      if(arguments.indexs != NULL){
	ix_p = arguments.indexs;
      } else ix_p = NULL;

      for (i = 0; i < ndims; i++){
	if (ix_p != NULL) {
          indexs[i] = ncsel_strtoi (ix_p, indexs_dim + i);
	  ix_p = strchr (ix_p, ','); 
	  if (ix_p != NULL)
            ix_p++;
	} else indexs[i] = NULL;

        if (indexs[i] == NULL) {
          long dim;
          /* FIXME: check for a failure */
	  indexs[i] = calloc(2, sizeof(int));
	  ncdiminq(ncid, dimids[i], (char *) 0 , &dim);
	  indexs[i][1] = dim - 1;
	  indexs_dim[i] = 1;
	}
      }

      ncopts = 0;    
      if(isnan(arguments.add_offset)){
	if (ncattget(ncid, varid, "add_offset", &add_offset) == -1)
	  add_offset = 0;
      }
      else add_offset = arguments.add_offset;
      if(isnan(arguments.scale_factor)){
	if (ncattget(ncid, varid, "scale_factor", &scale_factor) == -1)
	  scale_factor = 1;
      }
      else scale_factor = arguments.scale_factor;
      fill_value = malloc(8);
      if (ncattget(ncid, varid, "_FillValue", fill_value) == -1){
	free(fill_value);
	fill_value = NULL;
      }
      ncopts = NC_FATAL;

      data = ncsel (ncid, varid, indexs, indexs_dim, &data_len);
      if (data == 0) {
        error (1, errno, "Failed to get the values");
      }

      {
        const struct output_conversion conv = {
          .output_type = arguments.output_type,
          .coeffs = {
            arguments.multiply * add_offset,
            arguments.multiply * scale_factor
          },
          .map_to_nan = fill_value
        };
        dump_array (data, data_type, data_len, &conv, output);
      }
    }
  }

  close_file (output);

  return 0;
}

/*** ncget.c ends here */
