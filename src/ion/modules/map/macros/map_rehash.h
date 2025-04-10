/**
 * Defines the `map_rehash` function for a type declined map. */
#define map_rehash(kt, vt) \
  map_rehash__ ## kt ## __ ## vt
