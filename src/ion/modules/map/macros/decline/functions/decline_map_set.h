#define decline_map_set(kt, vt)                                                     _L_ \
                                                                                    _L_ \
vt* map_set(kt, vt) (                                                               _L_ \
    map(kt, vt)* m,                                                                 _L_ \
    kt* key,                                                                        _L_ \
    vt* value                                                                       _L_ \
)                                                                                   _L_ \
{                                                                                   _L_ \
  u64 key_hash = map_hasher(kt, vt)(key);                                           _L_ \
  u64 probe_index = key_hash & (m->capacity - 1);                                   _L_ \
  u64 probe_index_limit = m->capacity + MAP_CAPACITY_PADDING - 1;                   _L_ \
                                                                                    _L_ \
linear_probing:                                                                     _L_ \
  kt* probed_key = map_key_at(m, probe_index);                                      _L_ \
  if (map_entry_is_empty(m, probe_index))                                           _L_ \
    goto set_value_new;                                                             _L_ \
                                                                                    _L_ \
  if (map_comparer(kt, vt)(key, probed_key))                                        _L_ \
    goto set_value_existing;                                                        _L_ \
                                                                                    _L_ \
  probe_index++;                                                                    _L_ \
  if (probe_index >= probe_index_limit)                                             _L_ \
    probe_index = 0;                                                                _L_ \
                                                                                    _L_ \
  goto linear_probing;                                                              _L_ \
                                                                                    _L_ \
set_value_new:                                                                      _L_ \
  *probed_key = *key;                                                               _L_ \
  map_entry_occupy(m, probe_index, key_hash);                                       _L_ \
  m->length++;                                                                      _L_ \
                                                                                    _L_ \
set_value_existing:                                                                 _L_ \
  *map_value_at(m, probe_index) = *value;                                           _L_ \
                                                                                    _L_ \
  if (m->length >= m->load_limit)                                                   _L_ \
    map_rehash(kt, vt)(m);                                                          _L_ \
                                                                                    _L_ \
  return value;                                                                     _L_ \
}
