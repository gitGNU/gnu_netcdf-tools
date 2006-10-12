#define _GNU_SOURCE
#define _ISOC99_SOURCE
#include "hdfdump.h"
/* my useful macros for debuging */ 
#include "my_debug.h"
/* ------------------------------ */ 

/* for parsing command line options */
#include <argp.h>
/* -------------------------------- */



const char *argp_program_version =
"hdfdump 1.0";
const char *argp_program_bug_address =
"<anton@modis.ru>";

/* Program documentation. */
static char doc[] = "Dump an SDS or an attribute of the HDF file";
/* A description of the arguments we accept. */
static char args_doc[] = ("[OPTION] FILE SDS\n"
			  "[OPTION] FILE SDS:ATTRIBUTE");

/* Keys for options without short-options. */
/* ---- */
    
/* The options we understand. */

static struct argp_option options[] = {
  { 0, 0, 0, 0, "output format selection"},
  { "float32",  'f', NULL, 0, "float32 format" },
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
};

/* Parse a single option. */
static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
  /* Get the `input' argument from `argp_parse', which we
     know is a pointer to our arguments structure. */
  struct arguments *arguments = state->input;
  char *tmp;

  switch (key) {
  case 'f':
    arguments->output_type = OUTTYPE_FLOAT;
    break;

  case 'T':
    arguments->output_type = OUTTYPE_TEXT;
    break;

  case 'R':
    arguments->output_type = OUTTYPE_RAW;
    break;
    
  case 'S':
    arguments->shape = 1;
    break;

  case 'i':
    arguments->info = 1;
    break;

  case 'm':
    arguments->multiply = strtod (arg, &tmp);
    if(arg == tmp) {
      arguments->multiply = 1;
      error (0, errno, "%s - invalid number", arg);
    }
    break;
  case 'a':
    arguments->add_offset = strtod (arg, &tmp);
    if(arg == tmp) {
      arguments->add_offset = NAN;
      error (0, errno, "%s - invalid number", arg);
    }
    break;
  case 's':
    arguments->scale_factor = strtod (arg, &tmp);
    if(arg == tmp) {
      arguments->scale_factor = NAN;
      error (0, errno, "%s - invalid number", arg);
    }
    break;

  case ARGP_KEY_ARG:
    if(arguments->input_file == NULL){
      arguments->input_file = strdup(arg);
    }
    else if(arguments->sds_name == NULL && arguments->attribute_name == NULL){
      tmp = strchr(arg, ':');
      if(tmp == NULL){
	arguments->sds_name = strdup(arg);
      }
      else {
	arguments->attribute_name = strdup(tmp + 1);
	if(tmp == arg){
	  arguments->sds_name = NULL;
	}
	else{ 
	  arguments->sds_name = malloc((tmp - arg + 1) * sizeof(char));
	  strncpy(arguments->sds_name, arg, tmp - arg);
	  arguments->sds_name[tmp - arg] = '\0';
	}
      }
    } else if(arguments->indexs == NULL){
      arguments->indexs = strdup(arg);
    }else {
      argp_error (state, "too many non-option arguments given");
      return EINVAL;
    }
    
    break;
  case ARGP_KEY_END:
    if(arguments->sds_name == NULL && arguments->attribute_name == NULL){
      argp_error (state, "not enough non-option arguments given");
      return EINVAL;
    }
    
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
  int varid;
  int data_len;
  int i;
  void *Ptr;
  void *dump, *fill_value;
  char sds_name[MAX_NC_NAME];
  nc_type data_type;
  int ndims, dimids[MAX_VAR_DIMS], natts;
  int **indexs, *indexs_dim;
  char *tmp;
  long long_tmp;
  double add_offset,  scale_factor;
  
  /* Default values.                  */
  add_offset               = 0;
  scale_factor             = 1;
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
  
  ncid = ncopen(arguments.input_file, NC_NOWRITE);

  if(arguments.attribute_name != NULL){
    if(arguments.output_type == OUTTYPE_DEFAULT) 
      arguments.output_type = OUTTYPE_TEXT;
    
    if(arguments.sds_name != NULL)
      varid = ncvarid (ncid, arguments.sds_name);
    else 
      varid = NC_GLOBAL;
    
    ncattinq(ncid, varid, arguments.attribute_name, &data_type, &data_len);
    if(arguments.shape)
      printf("%d\n", data_len);
    else if(arguments.info) {
      hdf_print_attribute_info(ncid, varid, arguments.attribute_name, 0);
    } else {
      Ptr = hdf_memory_allocate(data_type, data_len);
      ncattget(ncid, varid, arguments.attribute_name, Ptr);
      hdf_dump_array(Ptr, data_type, data_len, arguments.multiply, arguments.output_type,
		     add_offset, scale_factor, NULL);
    }
  } else {
    varid = ncvarid (ncid, arguments.sds_name);
    ncvarinq(ncid, varid, sds_name, &data_type, &ndims, dimids, &natts);


    
    if(arguments.shape){
	ncdiminq(ncid, dimids[0], (char *) 0 , &long_tmp);
	printf("%ld", long_tmp);
      for (i = 1; i < ndims; i++){
	ncdiminq(ncid, dimids[i], (char *) 0 , &long_tmp);
	printf(" %ld", long_tmp);
      }
      printf("\n");
    } else if(arguments.info){
      hdf_print_sds_info(ncid, varid);
    } else {
      if(arguments.output_type == OUTTYPE_DEFAULT) 
	arguments.output_type = OUTTYPE_RAW;
    
      /* parsing of indexs */
    
      indexs = calloc(ndims, sizeof(int *));
      indexs_dim = calloc(ndims, sizeof(int));
      
      if(arguments.indexs != NULL){
	tmp = arguments.indexs;
      } else tmp = NULL;
      
      for (i = 0; i < ndims; i++){
	if (tmp != NULL){
	  indexs[i] = str2indexs(tmp, &(indexs_dim[i]));
	  tmp = strchr(tmp, ','); 
	  if(tmp != NULL) tmp++;
	}
	else indexs[i] = NULL;
	
	if(indexs[i] == NULL){ /* str2indexs can return NULL */
	  indexs[i] = calloc(2, sizeof(int));
	  ncdiminq(ncid, dimids[ndims - i - 1], (char *) 0 , &long_tmp);
	  indexs[i][1] = long_tmp - 1;
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

      dump = selection(ncid, varid, indexs, indexs_dim, &data_len);
      
      hdf_dump_array(dump, data_type, data_len, arguments.multiply, arguments.output_type,
		     add_offset, scale_factor, fill_value);      
    }
    
    // test
    /*     for (i = 0; i < ndims; i++){ */
    /*       printf("dim[%d] = %d\n", i, indexs_dim[i]); */
    /*       for (j = 0; j < indexs_dim[i]; j++){ */
    /* 	printf("[%d ; %d]\n", indexs[i][j * 2], indexs[i][j * 2 + 1]); */
    /*       } */
    /*     } */
    
  }
  
  //    varid = ncvarid(ncid, arguments.sds_name);  
  return 0;
}
