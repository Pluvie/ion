void map_print (
    struct map* map
)
{
  u64 probed_capacity = map->capacity + log2(map->capacity);

  for (u64 index = 0; index < probed_capacity; index++) {
    fprintf(stderr, "-----------\n");
    fprintf(stderr, "%9li |\n", index);
    fprintf(stderr, "-----------\n");

    byte* key = (byte*) map->keys + (index * map->key_typesize);
    byte* value = (byte*) map->values + (index * map->value_typesize);
    u64 hash = map->hashes[index];

    if (hash == -1) {
      fprintf(stderr, "         --\n");
      continue;
    }

    hexdump(key, map->key_typesize);
    fprintf(stderr, "-----------\n");
    hexdump(value, map->value_typesize);
  }
}
