/**
 * Defines the `map_del` function for a type declined map. */
#define map_del(kt, vt) \
  map_del__ ## kt ## __ ## vt
