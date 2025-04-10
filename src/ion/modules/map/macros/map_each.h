// ITERATOR IDEAS ---- TODO
//typedef struct {
//  kt* key;
//  vt* value;
//  u64 index;
//  u64 hash;
//} map_iterator(kt, vt);
//
//map_iterator(i32, i32) iter = { 0 };
//for map_each(m, &iter) {
//  
//}
//
//map_each(m, iter)
//  (u64 i = 0; i < (m)->capacity + MAP_CAPACITY_PADDING; i++)
//    if (iter.key = map_key_at(m, i), iter.value = map_value_at(m, i), !map_entry_is_empty(m, i))
//


/**
 * Loops through the keys and values of a map. A specific name for the index can be
 * provided as optional fifth argument. */
#define map_each(m, kt, key, vt, value, ...)                          \
  (key_type key = NULL; map != NULL && key != (void*) 1; key = (void*) 1)     \
    for (val_type val = NULL; val != (void*) 1; val = (void*) 1)              \
      for (u64 i = 0; i < (map)->capacity + log2((map)->capacity); i++)       \
      __VA_OPT__(for(u64 __VA_ARGS__ = i; __VA_ARGS__ != i; __VA_ARGS__++))   \
        if (key = (map)->keys + (i * (map)->key_typesize),                    \
            val = (map)->values + (i * (map)->value_typesize),                \
            (map)->hashes[i] != -1)
