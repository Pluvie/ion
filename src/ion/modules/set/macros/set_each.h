/**
 * Loops through the keys and values of the set, avoiding the empty spots. */
#define set_each(s, iter)                                                               \
  (u64 i = 0;                                                                           \
  i < (s)->capacity + MAP_CAPACITY_PADDING;                                             \
  !set_entry_is_empty(s, i) ? iter.index++ : 0, i++)                                    \
    if (iter.key = set_key_at(s, i),                                                    \
        iter.value = set_value_at(s, i),                                                \
        !set_entry_is_empty(s, i))
