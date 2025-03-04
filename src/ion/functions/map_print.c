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

    void* entry = map->entries + (index * map->entry_typesize);
    void* key = map_entry_key(map, entry);
    void* value = map_entry_value(map, entry);

    if (map_entry_is_empty(entry)) {
      fprintf(stderr, "         --\n");
      continue;
    }

    hexdump(key, map->key_typesize);
    fprintf(stderr, "-----------\n");
    hexdump(value, map->value_typesize);
  }
}
