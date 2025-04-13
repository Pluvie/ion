/**
 * Loops through the elements of an array. */
#define array_each(ary, iter)                                                           \
  (iter.index = 0; iter.index < (ary)->length; iter.index++)                            \
    if (iter.element = array_get(ary, iter.index), true)
