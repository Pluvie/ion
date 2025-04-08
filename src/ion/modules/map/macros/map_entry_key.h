/**
 * Retrieves the key of a map entry. */
#define map_entry_key(map, entry) \
  (entry + (map)->hash_typesize)
