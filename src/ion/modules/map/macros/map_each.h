/**
 * Loops through the keys and values of the map, avoiding the empty spots. */
#define map_each(m, iter)                                                               \
  (u64 i = 0;                                                                           \
  i < (m)->capacity + MAP_CAPACITY_PADDING;                                             \
  !map_entry_is_empty(m, i) ? iter.index++ : 0, i++)                                    \
    if (iter.key = map_key_at(m, i),                                                    \
        iter.value = map_value_at(m, i),                                                \
        !map_entry_is_empty(m, i))
