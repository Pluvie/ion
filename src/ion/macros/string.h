/*
  Helper to create a `string` type from double quoted literal.
*/
#define string(str) \
  (string) { str, sizeof(str) - 1 }
