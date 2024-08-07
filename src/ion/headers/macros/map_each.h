/**
 * Loops through the keys and values of a map. */
#define map_each(map, key_type, key, val_type, val)                           \
  (key_type key = NULL; map != NULL && key != (void*) 1; key = (void*) 1)     \
    for (val_type val = NULL; val != (void*) 1; val = (void*) 1)              \
      for (u64 i = 0; i < (map)->capacity + log2((map)->capacity); i++)       \
        if (key = (map)->keys + (i * (map)->key_typesize),                    \
            val = (map)->values + (i * (map)->value_typesize),                \
            (map)->hashes[i] != -1)
