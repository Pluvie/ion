/**
 * Checks if a set entry is empty. */
#define set_entry_is_empty(s, index) \
  (s)->hashes[index] == 0
