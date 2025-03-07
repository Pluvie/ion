/**
 * Loops through the values of a map. */
#define map_each_value(map, val_type, val)                                    \
  (val_type val = NULL; map != NULL && val != (void*) 1; val = (void*) 1)     \
    for (u64 i = 0; i < (map)->capacity + log2((map)->capacity); i++)         \
      if (val = (map)->values + (i * (map)->value_typesize),                  \
          (map)->hashes[i] != -1)
