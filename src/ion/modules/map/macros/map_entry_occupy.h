/**
 * Occupies an empty map entry. */
#define map_entry_occupy(hash) \
  (* (hash | (u64) 0x8000000000000000))
