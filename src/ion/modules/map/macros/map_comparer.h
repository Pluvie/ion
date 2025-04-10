/**
 * Defines a comparer for a type declined map. */
#define map_comparer(kt, vt) \
  map_comparer__ ## kt ## __ ## vt
