/* Defines the hash mask of a set.

  This mask reserves the first bit of the hash as a flag to determine whether the
  position is occupied.

  This is necessary because hash functions can return 0 as a valid value, but the
  set container is using the 0 value to identify free positions.

  Therefore, when occupying a position in the set, the hash is bit masked with this
  constant value to switch its first bit to 1. */
#ifndef SET_HASH_MASK
#define SET_HASH_MASK (((uint) 1) << (INT_BITSIZE - 1))
#else
#undef  SET_HASH_MASK
#endif

/* Calculates the set load limit given its capacity. */
#ifndef set_load_limit
#define set_load_limit(s) \
  (((s)->capacity * 70) / 100)
#else
#undef  set_load_limit
#endif

/* Check whether a set position is free or not. */
#ifndef set_pos_is_free
#define set_pos_is_free(s, p) \
  ((s)->hashes[p] == (uint) 0)
#else
#undef  set_pos_is_free
#endif

/* Check whether a set position is occupied or not. */
#ifndef set_pos_is_occupied
#define set_pos_is_occupied(s, p) \
  ((s)->hashes[p] != (uint) 0)
#else
#undef  set_pos_is_occupied
#endif

/* Occupies a set position. */
#ifndef set_pos_occupy
#define set_pos_occupy(s, p, h) \
  (s)->hashes[p] = ((uint) h | SET_HASH_MASK)
#else
#undef  set_pos_occupy
#endif

/* Empties a set position. */
#ifndef set_pos_free
#define set_pos_free(s, p) \
  (s)->hashes[p] = (uint) 0
#else
#undef  set_pos_free
#endif

/* Constant to represent an invalid set position. */
#ifndef set_pos_invalid
#define set_pos_invalid \
  ((uint) -1)
#else
#undef  set_pos_invalid
#endif
