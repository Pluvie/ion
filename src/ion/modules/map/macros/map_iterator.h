/**
 * Defines an iterator for a type declined map. */
#define map_iterator(kt, vt) \
  map_iterator__ ## kt ## __ ## vt
