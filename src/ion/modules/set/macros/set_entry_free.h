/**
 * Frees a set entry. */
#define set_entry_free(set, index) \
  (set)->hashes[index] = 0
