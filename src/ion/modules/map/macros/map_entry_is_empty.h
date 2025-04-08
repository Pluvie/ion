/**
 * Checks if a map entry is empty. */
#define map_entry_is_empty(map, entry)  \
  (*(u64*) entry == 0)
