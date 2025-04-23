void map_rehash(kt, vt) (
    map(kt, vt)* map
)
{
  u64 new_capacity = map->capacity * 2;
  map(kt, vt) rehashed_map = map_init(kt, vt)(new_capacity, map->allocator);

  for (u64 i = 0; i < map->capacity + MAP_CAPACITY_PADDING; i++) {
    if (map_entry_is_empty(map, i))
      continue;

    kt* key = map_key_at(map, i);
    vt* value = map_value_at(map, i);
    map_set(kt, vt)(&rehashed_map, key, value);
  }

  map->capacity = new_capacity;
  map->hashes = rehashed_map.hashes;
  map->keys = rehashed_map.keys;
  map->values = rehashed_map.values;
  map->load_limit = map_load_limit(new_capacity);
}
