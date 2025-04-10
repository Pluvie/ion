/**
 * Defines the `map_set` function for a type declined map. */
#define map_set(kt, vt) \
  map_set__ ## kt ## __ ## vt
