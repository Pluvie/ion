#ifdef ION_INCLUDED
static inline
#endif

void* map_set (
    struct map* map,
    void* key,
    void* value
)
{
  u64 hash = map_hash(key, map->key_typesize);
  u64 probe_index = hash & (map->capacity - 1);
  u64 probe_index_limit = map->capacity - 1;

  void* entry = map->entries + (probe_index * map->entry_typesize);

linear_probing:
  if (map_entry_is_empty(entry))
    goto set_value_new;

  if (memeq(key, map_entry_key(map, entry), map->key_typesize))
    goto set_value_existing;

  probe_index++;
  entry += map->entry_typesize;

  if (probe_index >= probe_index_limit) {
    entry = map->entries;
    probe_index = 0;
    goto linear_probing;
  }

  goto linear_probing;

set_value_new:
  memcpy(map_entry_key(map, entry), key, map->key_typesize);
  map_entry_occupy(entry, hash);
  map->length++;

set_value_existing:
  memcpy(map_entry_value(map, entry), value, map->value_typesize);

  if (map->length >= map->load_limit)
    map_rehash(map);

  return value;
}
