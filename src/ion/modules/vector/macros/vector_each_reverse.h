/**
 * Loops through the elements of a vector in reverse order. A specific name for
 * the index can be provided as optional fourth argument. */
#define vector_each_reverse(vector, elem_type, elem, ...)                         \
  (elem_type elem = NULL; vector != NULL && elem != (void*) 1; elem = (void*) 1)  \
    for (i64 i = (vector)->length - 1; i >= 0; i--)                               \
      __VA_OPT__(for(u64 __VA_ARGS__ = i; __VA_ARGS__ != i; __VA_ARGS__++))       \
      if (elem = (vector)->data + (i * (vector)->typesize), true)
