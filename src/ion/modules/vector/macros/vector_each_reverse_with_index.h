/**
 * Loops through the elements of a vector in reverse order and with a
 * specified index. */
#define vector_each_reverse_with_index(vector, idx, elem_type, elem)              \
  (elem_type elem = NULL; vector != NULL && elem != (void*) 1; elem = (void*) 1)  \
    for (i64 idx = (vector)->length - 1; idx >= 0; idx--)                         \
      if (elem = (vector)->data + (idx * (vector)->typesize), true)
