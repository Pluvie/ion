/**
 * Defines the `map_get` function for a type declined map. */
#define map_get(kt, vt) \
  map_get__ ## kt ## __ ## vt
