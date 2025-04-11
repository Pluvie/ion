/**
 * Frees a map entry. */
#define map_entry_free(m, index) \
  (m)->hashes[index] = 0
