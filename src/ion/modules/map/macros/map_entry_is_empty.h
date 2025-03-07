/**
 * Checks if a map entry is empty. */
#define map_entry_is_empty(entry)   \
  (*(u64*) entry == MAP_EMPTY_SPOT)
