#ifdef ION_INCLUDED
static inline
#endif

void map_print (
    struct map* map
)
{
  u64 probed_capacity = map->capacity + log2(map->capacity);

  for (u64 index = 0; index < probed_capacity; index++) {
    fprintf(stderr, "-----------\n");
    fprintf(stderr, "%9li |\n", index);
    fprintf(stderr, "-----------\n");

    u64* is_empty = map->entries + (index * map->entry_typesize);
    void* key = map->entries + (index * map->entry_typesize) + sizeof(u64);
    void* value = key + map->key_typesize;

    if (*is_empty == MAP_EMPTY_SPOT) {
      fprintf(stderr, "         --\n");
      continue;
    }

    hexdump(key, map->key_typesize);
    fprintf(stderr, "-----------\n");
    hexdump(value, map->value_typesize);
  }
}
