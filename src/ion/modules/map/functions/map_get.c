#ifdef ION_INCLUDED
static inline
#endif

void* map_get (
    struct map* map,
    void* key
)
{
  u64 key_hash = map_hash(key, map->key_typesize);
  u64 probe_index = key_hash & (map->capacity - 1);
  u64 probe_index_limit = map->capacity + MAP_PADDED_CAP - 1;

#if defined(__AVX512F__)
  #include "map_get__avx512.c"

#elsif defined(__AVX2__)
  #include "map_get__avx2.c"

#else
  void* entry = map->entries + (probe_index * map->entry_typesize);
  u32* hash = map->hashes + probe_index;

linear_probing:
  if (map_hash_is_empty(hash))
    return NULL;

  if (memeq(key, map_entry_key(map, entry), map->key_typesize))
    goto return_value;

  hash++;
  probe_index++;
  entry += map->entry_typesize;

  if (probe_index >= probe_index_limit) {
    entry = map->entries;
    hash = map->hashes;
    probe_index = 0;
  }

  goto linear_probing;

return_value:
  return map_entry_value(map, entry);
#endif
}
