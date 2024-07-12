/**
 * Helper to create a string from double quoted literal. */
#define s(str) \
  (struct string) { .content = str, .length = sizeof(str) - 1 }
