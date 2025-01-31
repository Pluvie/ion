/**
 * Helper to test the equality of two strings, case insensitive, with a maximum size. */
#define strncaseeq(s1, s2, n) \
  (strncasecmp(s1, s2, n) == 0)
