/**
 * Frees a set entry. */
#define set_entry_free(s, index) \
  (s)->hashes[index] = 0
