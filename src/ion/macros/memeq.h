/**
 * Helper to check the equality of two memory pointers. */
#define memeq(s1, s2, n) \
  (memcmp(s1, s2, n) == 0)
