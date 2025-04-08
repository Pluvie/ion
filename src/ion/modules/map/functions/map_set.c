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

//#if defined(__AVX512F__)
//  #include "map_set__avx512.c"
//
//#elif defined(__AVX2__)
//  #include "map_set__avx2.c"
//
//#else
linear_probing:
  void* entry = map->entries + (probe_index * map->entry_typesize);

  if (map_entry_is_empty(map, entry))
    goto set_value_new;

  if (map->key_typesize <= sizeof(u64)) {
    if (*(u64*) key == *(u64*) map_entry_key(map, entry))
      goto set_value_existing;

  } else {
    if (memeq(key, map_entry_key(map, entry), map->key_typesize))
      goto set_value_existing;
  }

  probe_index++;
  if (probe_index >= probe_index_limit)
    probe_index = 0;

  goto linear_probing;

set_value_new:
  memcpy(map_entry_key(map, entry), key, map->key_typesize);
  map_entry_occupy(map, entry, key_hash);
  map->length++;

set_value_existing:
  memcpy(map_entry_value(map, entry), value, map->value_typesize);

  if (map->length >= map->load_limit)
    map_rehash(map);

  return value;
//#endif
}
