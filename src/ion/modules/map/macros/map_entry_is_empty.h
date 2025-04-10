/**
 * Checks if a map entry is empty. */
#define map_entry_is_empty(m, index) \
  m->hashes[index] == 0
