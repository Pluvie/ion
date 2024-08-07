/**
 * Loops through the elements of an array. */
#define array_each(array, elem_type, elem)                                  \
  (elem_type elem = NULL; elem != (void*) 1; elem = (void*) 1)              \
    for (u64 i = 0; i < (array)->length; i++)                               \
      if (elem = (elem_type) (array)->data + (i * (array)->typesize), true)
