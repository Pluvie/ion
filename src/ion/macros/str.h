/* Helper to create a `str` type from double quoted literal. */
#define str(literal) \
  (str) { literal, sizeof(literal) - 1 }
