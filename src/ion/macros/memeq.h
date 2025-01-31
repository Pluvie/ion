/**
 * Helper to test the equality of two memory regions. */
#define memeq(s1, s2, n) \
  (memcmp(s1, s2, n) == 0)
