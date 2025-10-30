/* Helper to create a `str` type from double quoted literal. */
#define str(literal) \
  { literal, sizeof(literal) - 1 }
