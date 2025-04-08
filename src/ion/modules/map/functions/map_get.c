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
  void* observed_key = map_key_at(map, probe_index);
  if (map_key_equal(map, key, observed_key))
    return map_value_at(map, probe_index);

  if (map_entry_is_empty(map, probe_index))
    return NULL;

  probe_index++;
  if (probe_index >= probe_index_limit)
    probe_index = 0;

  goto linear_probing;
//#endif
}
