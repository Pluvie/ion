/**
 * Loops through the elements of a vector. */
#define vector_each(vector, elem_type, elem)                                      \
  (elem_type elem = NULL; vector != NULL && elem != (void*) 1; elem = (void*) 1)  \
    for (u64 i = 0; i < (vector)->length; i++)                                    \
      if (elem = (vector)->data + (i * (vector)->typesize), true)
