static inline void map_rehash (
    struct map* map
)
{
  u64 new_capacity = map->capacity * 2;

rehash_begin:
  struct map rehashed_map = map_init(
    map->key_typesize, map->value_typesize, new_capacity, map->allocator);

  void* key;
  void* value;
  u64 probed_capacity = map->capacity + log2(map->capacity);

  for (u64 i = 0; i < probed_capacity; i++) {
    if (*(map->hashes + i) == -1)
      continue;

    key = map->keys + (i * map->key_typesize);
    value = map->values + (i * map->value_typesize);

    /* This code is very important to protect the map from a double rehash, which
     * occurs when the map is doing a rehash and the rehashing key falls over the
     * probed capacity (see `map_set_rehash` function for more details on the
     * probing algorithm).
     *
     * This would trigger a rehash within a rehash, which is inconsistent and wrong,
     * because, if allowed, it will lose keys since the first rehash is not yet
     * completed.
     *
     * If this happens, the `map_set_rehash` function returns `NULL` and the rehash
     * is aborted and started again, doubling the already doubled capacity. */
    if (map_set_rehash(&rehashed_map, key, value, true) == NULL) {
      new_capacity *= 2;
      goto rehash_begin;
    }
  }

  map->capacity = new_capacity;
  map->keys = rehashed_map.keys;
  map->values = rehashed_map.values;
  map->hashes = rehashed_map.hashes;
}
