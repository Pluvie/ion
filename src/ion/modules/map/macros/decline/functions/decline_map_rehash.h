#define decline_map_rehash(kt, vt)                                                  _L_ \
                                                                                    _L_ \
void map_rehash(kt, vt) (                                                           _L_ \
    map(kt, vt)* m                                                                  _L_ \
)                                                                                   _L_ \
{                                                                                   _L_ \
  u64 new_capacity = m->capacity * 2;                                               _L_ \
  map(kt, vt) rehashed_map = map_init(kt, vt)(new_capacity, m->allocator);          _L_ \
                                                                                    _L_ \
  for (u64 i = 0; i < m->capacity + MAP_CAPACITY_PADDING; i++) {                    _L_ \
    if (map_entry_is_empty(m, i))                                                   _L_ \
      continue;                                                                     _L_ \
                                                                                    _L_ \
    kt* key = map_key_at(m, i);                                                     _L_ \
    vt* value = map_value_at(m, i);                                                 _L_ \
    map_set(kt, vt)(&rehashed_map, key, value);                                     _L_ \
  }                                                                                 _L_ \
                                                                                    _L_ \
  m->capacity = new_capacity;                                                       _L_ \
  m->hashes = rehashed_map.hashes;                                                  _L_ \
  m->keys = rehashed_map.keys;                                                      _L_ \
  m->values = rehashed_map.values;                                                  _L_ \
  m->load_limit = map_load_limit(new_capacity);                                     _L_ \
}
