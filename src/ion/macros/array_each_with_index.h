/**
 * Loops through the elements of an array with a specified index. */
#define array_each_with_index(array, idx, elem_type, elem)                        \
  (elem_type elem = NULL; array != NULL && elem != (void*) 1; elem = (void*) 1)   \
    for (u64 idx = 0; idx < (array)->length; idx++)                               \
      if (elem = (array)->data + (idx * (array)->typesize), true)
