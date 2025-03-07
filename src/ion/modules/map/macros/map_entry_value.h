/**
 * Retrieves the value of a map entry. */
#define map_entry_value(map, entry)     \
  ((void*) entry + sizeof(u64) + (map)->key_typesize)
