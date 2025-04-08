/**
 * Retrieves the key of a map. */
#define map_key_at(map, index)  \
  ((map)->keys + (index * (map)->key_typesize))
