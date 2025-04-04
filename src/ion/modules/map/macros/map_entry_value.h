/**
 * Retrieves the value of a map entry. */
#define map_entry_value(map, entry)     \
  ((void*) entry + (map)->key_typesize)
