static inline void* map_set_rehash (
    struct map* map,
    void* key,
    void* value,
    bool rehashing
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
    goto set_value_new;

  if (*hashes == capped_hash && memeq(key, comparing_key, map->key_typesize))
    goto set_value_existing;

  hashes++;
  probe_count++;
  comparing_key += map->key_typesize;

  if (probe_count >= probe_limit) {
    if (rehashing)
      return NULL;

    map_rehash(map);
    return map_set(map, key, value);
  }

  goto linear_probing;

set_value_new:
  memcpy(comparing_key, key, map->key_typesize);
  *hashes = capped_hash;
  map->length++;

set_value_existing:
  void* value_address = map->values + ((capped_hash + probe_count) * map->value_typesize);
  memcpy(value_address, value, map->value_typesize);
  return value;
}
