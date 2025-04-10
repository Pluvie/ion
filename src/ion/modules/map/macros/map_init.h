/**
 * Defines the `map_init` function for a type declined map. */
#define map_init(kt, vt) \
  map_init__ ## kt ## __ ## vt
