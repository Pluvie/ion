vt* map_(get, kt, vt) (
    map(kt, vt)* m,
    kt* key
)
{
  u64 key_hash = map_(hasher, kt, vt)(key);
  u64 probe_index = key_hash & (m->capacity - 1);
  u64 probe_index_limit = m->capacity + MAP_CAPACITY_PADDING - 1;

linear_probing:
  if (map_(comparer, kt, vt)(key, map_key_at(m, probe_index)))
    return map_value_at(m, probe_index);

  if (map_entry_is_empty(m, probe_index))
    return NULL;

  probe_index++;
  if (probe_index >= probe_index_limit)
    probe_index = 0;

  goto linear_probing;
}
