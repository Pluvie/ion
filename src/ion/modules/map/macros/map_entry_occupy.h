/**
 * Occupies a map entry. */
#define map_entry_occupy(map, index, hash) \
  (map)->hashes[index] = ((u64) hash | (u64) 0x8000000000000000)
