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

    void* key = map_key_at(map, index);
    void* value = map_value_at(map, index);

    if (map_entry_is_empty(map, index)) {
      fprintf(stderr, "         --\n");
      continue;
    }

    hexdump(key, map->key_typesize);
    fprintf(stderr, "-----------\n");
    hexdump(value, map->value_typesize);
  }
}
