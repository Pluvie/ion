/**
 * Loops through the elements of an array in reverse order. */
#define array_each_reverse(ary, iter)                                                   \
  (iter.index = (ary->length); (i64) iter.index > 0; iter.index--)                      \
    if (iter.element = array_get(ary, iter.index), true)
