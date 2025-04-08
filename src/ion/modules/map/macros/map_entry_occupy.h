/**
 * Occupies a map entry. */
#define map_entry_occupy(map, index, hash)  \
  (*((map)->hashes + index) = hash)
