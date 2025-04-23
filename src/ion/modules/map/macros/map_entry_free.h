/**
 * Frees a map entry. */
#define map_entry_free(map, index) \
  (map)->hashes[index] = 0
