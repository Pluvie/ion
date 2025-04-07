/**
 * Occupies an empty map entry. */
#define map_hash_occupy(hash, key_hash) \
  (*(hash) = (key_hash | (u32) 0x80000000))
