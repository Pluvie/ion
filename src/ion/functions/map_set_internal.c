static inline void* map_set_internal (
    struct map* map,
    void* key,
    void* value,
    bool rehashing
)
{
  u64 probe_limit = log2(map->capacity);
  u64 probe_count = 0;

  u64 hash = map_hash(key, map->key_typesize);
  u64 hash_index = hash & (map->capacity - 1);

  void* entry = map->entries + (hash_index * map->entry_typesize);

linear_probing:
  if (*(u64*) entry == MAP_EMPTY_SPOT)
    goto set_value_new;

  if (memeq(key, entry + sizeof(u64), map->key_typesize))
    goto set_value_existing;

  probe_count++;
  entry += map->entry_typesize;

  if (probe_count >= probe_limit) {
    if (rehashing)
      return NULL;

    map_rehash(map);
    return map_set(map, key, value);
  }

  goto linear_probing;

set_value_new:
  memcpy(entry + sizeof(u64), key, map->key_typesize);
  *(u64*) entry = !MAP_EMPTY_SPOT;
  map->length++;

set_value_existing:
  memcpy(entry + sizeof(u64) + map->key_typesize, value, map->value_typesize);
  return value;
}
