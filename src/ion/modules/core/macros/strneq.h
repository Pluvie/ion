/**
 * Helper to test the equality of two strings, with a maximum size. */
#define strneq(s1, s2, n) \
  (strncmp(s1, s2, n) == 0)
