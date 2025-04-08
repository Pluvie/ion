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

//#if defined(__AVX512F__)
//  #include "map_get__avx512.c"
//
//#elif defined(__AVX2__)
//  #include "map_get__avx2.c"
//
//#else
linear_probing:
  void* entry = map->entries + (probe_index * map->entry_typesize);

  if (map->key_typesize <= sizeof(u64)) {
    if (*(u64*) key == *(u64*) map_entry_key(map, entry))
      return map_entry_value(map, entry);

  } else {
    if (memeq(key, map_entry_key(map, entry), map->key_typesize))
      return map_entry_value(map, entry);
  }

  if (map_entry_is_empty(map, entry))
    return NULL;

  probe_index++;
  if (probe_index >= probe_index_limit)
    probe_index = 0;

  goto linear_probing;
//#endif
}
