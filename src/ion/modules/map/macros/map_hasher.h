/**
 * Defines a hasher for a type declined map. */
#define map_hasher(kt, vt) \
  map_hasher__ ## kt ## __ ## vt
