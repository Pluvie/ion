/**
 * Checks if a map entry is empty. */
#define map_entry_is_empty(map, index)  \
  (*((map)->hashes + index) == 0)
