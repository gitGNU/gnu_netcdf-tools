/*** ncsel.c --- The ncsel () and ncsel_strtoi () functions  -*- C -*- */

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
#include "ncget.h"


/* my useful macros for debuging */ 
//#include "my_debug.h"
/* ------------------------------ */ 


/* 0 1 2 1..2 , 1 2 3 */
#define BUFSIZE 1024

/* Useful macros */
#define CASS(x, y) ((x) = (typeof (x))(y))
#define MALLOC_VAR(x)     (CASS ((x), malloc             (sizeof (*(x)))))
#define MALLOC_ARY(x, y)  (CASS ((x), malloc       ((y) * sizeof (*(x)))))
#define CALLOC_ARY(x, y)  (CASS ((x), calloc       ((y),  sizeof (*(x)))))
#define REALLOC_ARY(x, y) (CASS ((x), realloc ((x), (y) * sizeof (*(x)))))

int *
ncsel_strtoi (char *string, int *index)
{
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

void *
ncsel (int ncid, int varid,
       const int **set, const int *sizes, 
       int *number_of_point)
{
  void *result, *ptr;
  int i;
  char name[MAX_NC_NAME];
  nc_type data_type;
  int ndims, dimids[MAX_VAR_DIMS], natts;
  int divisor[MAX_VAR_DIMS], n_combination;
  long *start, *vector;
  size_t values_count;
  int elt_sz;

  /* obtain the size of the element */
  ncvarinq(ncid, varid, name, &data_type, &ndims, dimids, &natts);
  if ((elt_sz = nctypelen (data_type)) == -1) {
    errno = EINVAL;
    return NULL;
  }

  /* calculation number of points and ... */
  values_count = 1;
  n_combination = 1;
  for (i = 0; i < ndims; i++){
    int j;
    int sum;

    n_combination *= sizes[i];
    sum = 0;
    for(j = 0; j < sizes[i]; j++)
      sum += set[i][j * 2 + 1] - set[i][j * 2] + 1;
    values_count *= sum; 
  }
  /* allocate memory */
  if ((result = malloc (elt_sz * values_count)) == 0) {
    return 0;
  }

  for (i = 0; i < ndims; i++){
    int j;
    divisor[i] = 1;
    for(j = i + 1; j < ndims; j++)
      divisor[i] *= sizes[j];
  }
  
  if (MALLOC_ARY (start, ndims) == 0) {
    free (result);
    return NULL;
  } else if (MALLOC_ARY (vector, ndims) == 0) {
    free (result);
    free (vector);
    return NULL;
  }

  ptr = result;
  for (i = 0; i < n_combination; i++){
    size_t length;
    int j;

    for (length = 1, j = 0; j < ndims; j++) {
      const int *p = &(set[j][i / divisor[j] % sizes[j] * 2]);
      const int
        from = p[0],
        len  = p[1] - from + 1;
      start[j]  = from;
      vector[j] = len;
      length   *= len;
      /* fprintf (stderr, "%d: %d+%d => %d\n", j, len, from, length); */
    }

    ncvarget (ncid, varid, start, vector, ptr); 
    ptr += length * elt_sz;
  }

  if (number_of_point != 0)
    *number_of_point = values_count;

  return result;
}

/*** ncsel.c ends here */
