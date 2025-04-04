/**
 * Returns the entry typesize of a map. */
#define map_entry_typesize(map)  \
  ((map)->key_typesize + (map)->value_typesize)
