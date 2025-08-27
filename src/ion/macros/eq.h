/**
 * Shorthand to compare two types and return `true` if they are equal. */
#define eq(...) \
  (cmp(__VA_ARGS__) == 0)
