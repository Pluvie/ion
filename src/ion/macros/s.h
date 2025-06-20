/**
 * Helper to create a string from double quoted literal. */
#define s(str) \
  (string) { str, lengthof(str) }
