/**
 * Loops through the elements of a vector with a specified index. */
#define vector_each_with_index(vector, idx, elem_type, elem)                      \
  (elem_type elem = NULL; vector != NULL && elem != (void*) 1; elem = (void*) 1)  \
    for (u64 idx = 0; idx < (vector)->length; idx++)                              \
      if (elem = (vector)->data + (idx * (vector)->typesize), true)
