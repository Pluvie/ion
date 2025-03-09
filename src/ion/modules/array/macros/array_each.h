/**
 * Loops through the elements of an array. A specific name for the index can be
 * provided as optional fourth argument. */
#define array_each(array, elem_type, elem, ...)                                   \
  (elem_type elem = NULL; array != NULL && elem != (void*) 1; elem = (void*) 1)   \
    for (u64 i = 0; i < (array)->length; i++)                                     \
      __VA_OPT__(for(u64 __VA_ARGS__ = i; __VA_ARGS__ == i; __VA_ARGS__++))       \
      if (elem = (array)->data + (i * (array)->typesize), true)
