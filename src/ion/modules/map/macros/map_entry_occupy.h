/**
 * Occupies a map entry. */
#define map_entry_occupy(m, index, hash) \
  (m)->hashes[index] = (hash | 0x8000000000000000)
