/**
 * Helper to test the equality of two strings. */
#define streq(s1, s2) \
  ((s1).length == (s2).length ? strncmp((s1).content, (s2).content, (s1).length) : false)
