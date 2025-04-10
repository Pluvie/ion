/**
 * Helper to test the equality of two strings, case insensitive. */
#define streq_case(s1, s2) \
  ((s1).length == (s2).length ? strncasecmp((s1).content, (s2).content, (s1).length) : false)
