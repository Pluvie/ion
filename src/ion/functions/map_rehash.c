static inline void map_rehash (
    struct map* map
)
{
  u64 new_capacity = map->capacity * 2;
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

    map_set(&rehashed_map, key, value);
  }

  map->capacity = new_capacity;
  map->keys = rehashed_map.keys;
  map->values = rehashed_map.values;
  map->hashes = rehashed_map.hashes;
}
