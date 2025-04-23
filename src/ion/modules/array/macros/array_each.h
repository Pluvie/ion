/**
 * Loops through the elements of an array. */
#define array_each(array, iter)                                                         \
  (; iter.index < (array)->length; iter.index++)                                        \
    if (iter.value = (array)->elements + iter.index, true)
