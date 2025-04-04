#ifdef ION_INCLUDED
static inline
#endif

void* map_set (
    struct map* map,
    void* key,
    void* value
)
{
  u64 key_hash = map_hash(key, map->key_typesize);
  u64 probe_index = key_hash & (map->capacity - 1);
  u64 probe_index_limit = map->capacity + MAP_PADDED_CAP - 1;

#if defined(__AVX512F__)
  #include "map_set__avx512.c"

#elsif defined(__AVX2__)
  #include "map_set__avx2.c"

#else
  void* entry = map->entries + (probe_index * map->entry_typesize);
  u32* hash = map->hashes + probe_index;

linear_probing:
  if (map_hash_is_empty(hash))
    goto set_value_new;

  if (memeq(key, map_entry_key(map, entry), map->key_typesize))
    goto set_value_existing;

  hash++;
  probe_index++;
  entry += map->entry_typesize;

  if (probe_index >= probe_index_limit) {
    hash = map->hashes;
    entry = map->entries;
    probe_index = 0;
  }

  goto linear_probing;

set_value_new:
  memcpy(map_entry_key(map, entry), key, map->key_typesize);
  map_hash_occupy(hash);
  map->length++;

set_value_existing:
  memcpy(map_entry_value(map, entry), value, map->value_typesize);

  if (map->length >= map->load_limit)
    map_rehash(map);

  return value;
#endif
}
