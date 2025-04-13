/**
 * Occupies a set entry. */
#define set_entry_occupy(s, index, hash) \
  (s)->hashes[index] = (hash | 0x8000000000000000)
