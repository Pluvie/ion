/**
 * Checks if a map entry is empty. */
#define map_hash_is_empty(hash)     \
  ((*(hash) & (u32) 0x80000000) == 0)
