/**
 * Loops through the elements of an array in reverse order. */
#define array_each_reverse(array, iter)                                                   \
  (iter.index = (array->length); (i64) iter.index > 0; iter.index--)                      \
    if (iter.value = array_get(array, iter.index), true)
