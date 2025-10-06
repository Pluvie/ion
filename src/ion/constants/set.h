/*
  Defines the hash mask of a set.

  This mask reserves the first bit of the hash as a flag to determine whether the
  position is occupied.

  This is necessary because hash functions can return 0 as a valid value, but the
  set container is using the 0 value to identify free positions.

  Therefore, when occupying a position in the set, the hash is bit masked with this
  constant value to switch its first bit to 1.
*/
#define SET_HASH_MASK (((unsigned int) 1) << (INT_BIT_WIDTH-1))
