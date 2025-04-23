/**
 * Occupies a set entry. */
#define set_entry_occupy(set, index, hash) \
  (set)->hashes[index] = ((u64) hash | (u64) 0x8000000000000000)
