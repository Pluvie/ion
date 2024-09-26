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
  u64 capped_hash = hash & (map->capacity - 1);
  u64* hashes = map->hashes + capped_hash;
  void* comparing_key = map->keys + (capped_hash * map->key_typesize);

linear_probing:
  if (*hashes == -1)
    return NULL;

  if (*hashes == capped_hash && memeq(key, comparing_key, map->key_typesize))
    goto return_value;

  hashes++;
  probe_count++;
  comparing_key += map->key_typesize;

  if (probe_count >= probe_limit)
    return NULL;

  goto linear_probing;

return_value:
  return map->values + ((capped_hash + probe_count) * map->value_typesize);
}
