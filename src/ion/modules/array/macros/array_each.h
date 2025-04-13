/**
 * Loops through the elements of an array. */
#define array_each(ary, iter)                                                           \
  (; iter.index < (ary)->length; iter.index++)                                          \
    if (iter.value = (ary)->elements + iter.index, true)
