/**
 * Loops through the keys of a map. */
#define map_each_key(map, key_type, key)                                      \
  (key_type key = NULL; map != NULL && key != (void*) 1; key = (void*) 1)     \
    for (u64 i = 0; i < (map)->capacity + log2((map)->capacity); i++)         \
      if (key = (map)->keys + (i * (map)->key_typesize),                      \
          (map)->hashes[i] != -1)
