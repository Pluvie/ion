/**
 * Retrieves the key of a map entry. */
#define map_entry_key(map, entry)     \
  ((void*) entry + sizeof(u64))
