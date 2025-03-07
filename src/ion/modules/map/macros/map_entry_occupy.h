/**
 * Occupies an empty map entry. */
#define map_entry_occupy(entry) \
  (*(u64*) entry = 1UL)
