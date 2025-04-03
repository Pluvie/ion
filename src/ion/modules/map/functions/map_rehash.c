static inline void map_rehash (
    struct map* map
)
{
  u64 new_capacity = map->capacity * 2;

rehash_begin:
  struct map rehashed_map = map_init(
    map->key_typesize, map->value_typesize, new_capacity, map->allocator);

  void* entry = map->entries;

  for (u64 i = 0; i < map->capacity; i++, entry += map->entry_typesize) {
    if (map_entry_is_empty(entry))
      continue;

    void* key = map_entry_key(map, entry);
    void* value = map_entry_value(map, entry);
    map_set(&rehashed_map, key, value);
  }

  map->capacity = new_capacity;
  map->load_limit = (new_capacity * 70) / 100,
  map->entries = rehashed_map.entries;
}
