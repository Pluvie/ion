/**
 * Retrieves the value of a map entry. */
#define map_entry_value(map, entry)     \
  (entry + (map)->hash_typesize + (map)->key_typesize)
