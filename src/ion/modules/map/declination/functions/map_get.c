vt* map_get(kt, vt) (
    map(kt, vt)* map,
    kt* key
)
{
  u64 key_hash = map_hasher(kt, vt)(key);
  u64 probe_index = key_hash & (map->capacity - 1);
  u64 probe_index_limit = map->capacity + MAP_CAPACITY_PADDING - 1;

linear_probing:
  if (map_comparer(kt, vt)(key, map_key_at(map, probe_index)))
    return map_value_at(map, probe_index);

  if (map_entry_is_empty(map, probe_index))
    return NULL;

  probe_index++;
  if (probe_index >= probe_index_limit)
    probe_index = 0;

  goto linear_probing;
}
