static inline void map_rehash (
    struct map* map
)
{
  u64 new_capacity = map->capacity * 2;

rehash_begin:
  struct map rehashed_map = map_init(
    map->key_typesize, map->value_typesize, new_capacity, map->allocator);

  //void* entry = map->entries;

  for (u64 i = 0;
      i < map->capacity + MAP_PADDED_CAP;
      i++) {
      //i++, entry += map->entry_typesize) {

    //if (map_entry_is_empty(map, entry))
    if (map_entry_is_empty(map, i))
      continue;

    //void* key = map_entry_key(map, entry);
    //void* value = map_entry_value(map, entry);
    void* key = map_key_at(map, i);
    void* value = map_value_at(map, i);
    map_set(&rehashed_map, key, value);
  }

  map->capacity = new_capacity;
  map->load_limit = map_load_limit(new_capacity);
  //map->entries = rehashed_map.entries;
  map->hashes = rehashed_map.hashes;
  map->keys = rehashed_map.keys;
  map->values = rehashed_map.values;
}
