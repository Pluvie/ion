/**
 * Loops through the elements of a vector in reverse order. */
#define vector_each_reverse(vector, elem_type, elem)                              \
  (elem_type elem = NULL; vector != NULL && elem != (void*) 1; elem = (void*) 1)  \
    for (i64 i = (vector)->length - 1; i >= 0; i--)                               \
      if (elem = (vector)->data + (i * (vector)->typesize), true)
