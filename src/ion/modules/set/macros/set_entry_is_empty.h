/**
 * Checks if a set entry is empty. */
#define set_entry_is_empty(set, index) \
  (set)->hashes[index] == 0
