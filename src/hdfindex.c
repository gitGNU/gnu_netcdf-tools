#include "hdfdump.h"


/* my useful macros for debuging */ 
//#include "my_debug.h"
/* ------------------------------ */ 


/* 0 1 2 1..2 , 1 2 3 */
#define BUFSIZE 1024

int * str2indexs(char * string, int *index){
  int *result, *tmp, length, interval; 
  char *tail;
  int next;

  *index = 0;
  interval = 0;
  length = BUFSIZE;
  result = malloc(length * sizeof(float));
  
  while (1) {
    
    while (isspace (*string)) string++;
    
    if (*string == 0 || *string == ',')
      break;
    /* There is more nonwhitespace,  */
    /* so it ought to be another number.  */
    //dd    fprintf(stderr, "string = %s\n",  string);
    /* Parse it.  */
    if(*string == '.' && *(string + 1) == '.' && !interval && index > 0){
      interval = 1;
      string++;
      string++;
      continue;
    } else if(! isdigit(*string)) {
      *index = -1;
      free(result);
      error (0, 0, "Not vailid symbol %c", *string);
      return NULL;
    } else 
      next = strtol (string, &tail, 0);
    
    /* Add it in, if not overflow.  */
    if (tail == string)
      error (EXIT_FAILURE, 0, "Overflow");
    string = tail;
    
    if(interval || (*index && next == result [*index * 2 - 1] + 1)){
      result [*index * 2 - 1] = next;
      interval = 0;
      continue;
    }
    else {
      result [*index * 2] = next;
      result [*index * 2 + 1] = next;
      (*index) += 1; 
      if(*index == length) { 
 	tmp = realloc(result, length + BUFSIZE); 
 	if(tmp == NULL) 
 	  error (EXIT_FAILURE, 0, "realloc error"); 
 	result = tmp; 
 	length += BUFSIZE; 
      } 
    }
  }
  if(*index == 0){
    free (result);
    return NULL;
  }
  return result;
}

void * selection(int ncid, int varid, int **set, int *sizes, 
		 int *number_of_point)
{
  void *result, *tmp;
  int i, j;
  char name[MAX_NC_NAME];
  nc_type data_type;
  int ndims, dimids[MAX_VAR_DIMS], natts;
  int divisor[MAX_VAR_DIMS], n_combination;
  int sum;
  int n;
  long *start, *vector;

  ncvarinq(ncid, varid, name, &data_type, &ndims, dimids, &natts);

  /* calculation number of points and ... */
  *number_of_point = 1;
  n_combination = 1;
  for (i = 0; i < ndims; i++){
    n_combination *= sizes[i];
    sum = 0;
    for(j = 0; j < sizes[i]; j++)
      sum += set[i][j * 2 + 1] - set[i][j * 2] + 1;
    *number_of_point *= sum; 
  }

  /* allocate memory */
  result = hdf_memory_allocate(data_type, *number_of_point);
  if(result == NULL){
    *number_of_point = 0;
    error(0, 0, "%s : Can't allocate memory", __FUNCTION__);
    return NULL;
  }

  for (i = 0; i < ndims; i++){
    divisor[i] = 1;
    for(j = i + 1; j < ndims; j++)
      divisor[i] *= sizes[j];
  }
  
  start = malloc(ndims * sizeof(long));
  vector = malloc(ndims * sizeof(long));
  tmp = result;
  for (i = 0; i < n_combination; i++){
    for(n = 1, j = 0; j < ndims; j++){
      start[ndims - j - 1] = set[j][i / (divisor[j]) % (sizes[j]) * 2];
      vector[ndims - j - 1] = set[j][i / (divisor[j]) % (sizes[j]) * 2 + 1] - 
	set[j][i / (divisor[j]) % (sizes[j]) * 2] + 1;
      n *= vector[j];
    }

    ncvarget(ncid, varid, start, vector, tmp); 

    switch(data_type) {
    case NC_BYTE:
    case NC_CHAR:
      tmp = tmp + n * 1;
      break;
      
    case NC_SHORT:
      tmp = tmp + n * 2;
      break;
      
    case NC_LONG:
    case NC_FLOAT:
      tmp = tmp + n * 4;
      break;
      
    case NC_DOUBLE:
      tmp = tmp + n * 8;
      
      break;
      
    default:
      return NULL;
    }
  }
  return result;
}

