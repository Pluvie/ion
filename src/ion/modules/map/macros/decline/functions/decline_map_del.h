#define decline_map_del(kt, vt)                                                     _L_ \
                                                                                    _L_ \
vt* map_del(kt, vt) (                                                               _L_ \
    map(kt, vt)* m,                                                                 _L_ \
    kt* key                                                                         _L_ \
)                                                                                   _L_ \
{                                                                                   _L_ \
  u64 key_hash = map_hasher(kt, vt)(key);                                           _L_ \
  u64 probe_index = key_hash & (m->capacity - 1);                                   _L_ \
  u64 probe_index_limit = m->capacity + MAP_CAPACITY_PADDING - 1;                   _L_ \
                                                                                    _L_ \
linear_probing:                                                                     _L_ \
  if (map_comparer(kt, vt)(key, map_key_at(m, probe_index))) {                      _L_ \
    map_entry_free(m, probe_index);                                                 _L_ \
    return map_value_at(m, probe_index);                                            _L_ \
  }                                                                                 _L_ \
                                                                                    _L_ \
  if (map_entry_is_empty(m, probe_index))                                           _L_ \
    return NULL;                                                                    _L_ \
                                                                                    _L_ \
  probe_index++;                                                                    _L_ \
  if (probe_index >= probe_index_limit)                                             _L_ \
    probe_index = 0;                                                                _L_ \
                                                                                    _L_ \
  goto linear_probing;                                                              _L_ \
}
