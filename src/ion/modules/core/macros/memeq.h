/**
 * Helper to test the equality of two memory regions. */
#define memeq(s1, s2, n) \
  (__builtin_memcmp(s1, s2, n) == 0)
