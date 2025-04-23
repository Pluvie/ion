/**
 * Loops through the keys and values of the set, avoiding the empty spots. */
#define set_each(set, iter)                                                             \
  (u64 i = 0;                                                                           \
  i < (s)->capacity + SET_CAPACITY_PADDING;                                             \
  !set_entry_is_empty(set, i) ? iter.index++ : 0, i++)                                  \
    if (iter.key = set_key_at(set, i),                                                  \
        iter.value = set_value_at(set, i),                                              \
        !set_entry_is_empty(set, i))
