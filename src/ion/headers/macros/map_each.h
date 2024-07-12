/**
 * Loops through the keys and values of a map. */
#define map_each(map, key, val)                                         \
  (void* key = NULL; key != (void*) 1; key = (void*) 1)                 \
    for (void* val = NULL; val != (void*) 1; val = (void*) 1)           \
      for (u64 i = 0; i < (map)->capacity + log2((map)->capacity); i++) \
        if (key = (byte*) (map)->keys + (i * (map)->key_typesize),      \
            val = (byte*) (map)->values + (i * (map)->value_typesize),  \
            (map)->hashes[i] != -1)
