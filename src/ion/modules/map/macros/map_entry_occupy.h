/**
 * Occupies an empty map entry. */
#define map_entry_occupy(entry, hash) \
  (*(u64*) entry = (hash | 0x8000000000000000))
