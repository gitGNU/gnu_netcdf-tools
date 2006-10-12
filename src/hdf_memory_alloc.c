#include "hdfdump.h"

void *
hdf_memory_allocate (nc_type datatype, size_t length)
{
  void *result;
  
  if(nctypelen(datatype) == -1){
    errno = EINVAL;
    return NULL;
  }
  result = malloc(length * nctypelen(datatype));
  
  return result;
}
