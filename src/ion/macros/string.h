/*
  Helper to create a `str` type from double quoted literal.
*/
#define string(literal) \
  (str) { literal, sizeof(literal) - 1 }
