vt* map_set(kt, vt) (
    map(kt, vt)* map,
    kt* key,
    vt* value
)
{
  u64 key_hash = map_hasher(kt, vt)(key);
  u64 probe_index = key_hash & (map->capacity - 1);
  u64 probe_index_limit = map->capacity + MAP_CAPACITY_PADDING - 1;

linear_probing:
  kt* probed_key = map_key_at(map, probe_index);
  if (map_entry_is_empty(map, probe_index))
    goto set_value_new;

  if (map_comparer(kt, vt)(key, probed_key))
    goto set_value_existing;

  probe_index++;
  if (probe_index >= probe_index_limit)
    probe_index = 0;

  goto linear_probing;

set_value_new:
  *probed_key = *key;
  map_entry_occupy(map, probe_index, key_hash);
  map->length++;

set_value_existing:
  *map_value_at(map, probe_index) = *value;

  if (map->length >= map->load_limit)
    map_rehash(kt, vt)(map);

  return value;
}
