/**
 * Loops through the elements of a vector. A specific name for the index can be
 * provided as optional fourth argument. */
#define vector_each(vector, elem_type, elem, ...)                                 \
  (elem_type elem = NULL; vector != NULL && elem != (void*) 1; elem = (void*) 1)  \
    for (u64 i = 0; i < (vector)->length; i++)                                    \
      __VA_OPT__(for(u64 __VA_ARGS__ = i; __VA_ARGS__ == i; __VA_ARGS__++))       \
      if (elem = (vector)->data + (i * (vector)->typesize), true)
