/**
 * Checks the byte equality of two pointers. */
#define byte_eq(v1, v2, len) \
  (byte_compare(v1, v2, len) == 0)
