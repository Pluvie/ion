/**
 * Occupies an empty map entry. */
#define map_hash_occupy(hash) \
  (*(hash) |= (u32) 0x80000000)
