#ifdef ION_INCLUDED
static inline
#endif

void map_print (
    struct map* map
)
{
  for (u64 index = 0; index < map->capacity + MAP_PADDED_CAP; index++) {
    fprintf(stderr, "-----------\n");
    fprintf(stderr, "%9li |\n", index);
    fprintf(stderr, "-----------\n");

    u32* hash = map->hashes + index;
    void* entry = map->entries + (index * map->entry_typesize);
    void* key = map_entry_key(map, entry);
    void* value = map_entry_value(map, entry);

    if (map_hash_is_empty(hash)) {
      fprintf(stderr, "         --\n");
      continue;
    }

    hexdump(key, map->key_typesize);
    fprintf(stderr, "-----------\n");
    hexdump(value, map->value_typesize);
  }
}
