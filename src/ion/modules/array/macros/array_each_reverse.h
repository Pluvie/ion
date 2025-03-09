/**
 * Loops through the elements of a narray in reverse order. A specific name for
 * the index can be provided as optional fourth argument. */
#define array_each_reverse(array, elem_type, elem, ...)                           \
  (elem_type elem = NULL; array != NULL && elem != (void*) 1; elem = (void*) 1)   \
    for (i64 i = (array)->length - 1; i >= 0; i--)                                \
      __VA_OPT__(for(u64 __VA_ARGS__ = i; __VA_ARGS__ != i; __VA_ARGS__++))       \
      if (elem = (array)->data + (i * (array)->typesize), true)
