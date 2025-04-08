/**
 * Occupies a map entry. */
#define map_entry_occupy(map, entry, hash)  \
  (*(u64*) (entry) = -1)
