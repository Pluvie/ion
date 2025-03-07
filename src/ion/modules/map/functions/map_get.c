#ifdef ION_INCLUDED
static inline
#endif

void* map_get (
    struct map* map,
    void* key
)
{
  u64 probe_limit = log2(map->capacity);
  u64 probe_count = 0;

  u64 hash = map_hash(key, map->key_typesize);
  u64 hash_index = hash & (map->capacity - 1);

  void* entry = map->entries + (hash_index * map->entry_typesize);

linear_probing:
  if (map_entry_is_empty(entry))
    return NULL;

  if (memeq(key, map_entry_key(map, entry), map->key_typesize))
    goto return_value;

  probe_count++;
  entry += map->entry_typesize;

  if (probe_count >= probe_limit)
    return NULL;

  goto linear_probing;

return_value:
  return map_entry_value(map, entry);
}
