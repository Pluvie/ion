void map_(rehash, kt, vt) (
    map(kt, vt)* m
)
{
  u64 new_capacity = m->capacity * 2;
  map(kt, vt) rehashed_map = map_(init, kt, vt)(new_capacity, m->allocator);

  for (u64 i = 0; i < m->capacity + MAP_CAPACITY_PADDING; i++) {
    if (map_entry_is_empty(m, i))
      continue;

    kt* key = map_key_at(m, i);
    vt* value = map_value_at(m, i);
    map_(set, kt, vt)(&rehashed_map, key, value);
  }

  m->capacity = new_capacity;
  m->hashes = rehashed_map.hashes;
  m->keys = rehashed_map.keys;
  m->values = rehashed_map.values;
  m->load_limit = map_load_limit(new_capacity);
}
