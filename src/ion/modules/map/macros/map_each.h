/**
 * Loops through the keys and values of the map, avoiding the empty spots. */
#define map_each(map, iter)                                                             \
  (u64 i = 0;                                                                           \
  i < (map)->capacity + MAP_CAPACITY_PADDING;                                           \
  !map_entry_is_empty(map, i) ? iter.index++ : 0, i++)                                  \
    if (iter.key = map_key_at(map, i),                                                  \
        iter.value = map_value_at(map, i),                                              \
        !map_entry_is_empty(map, i))
