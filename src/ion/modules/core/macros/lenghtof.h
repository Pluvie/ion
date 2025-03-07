/**
 * Same of #countof, but minus `1`.
 *
 * Useful for loops starting from `1`. */
#define lengthof(array) \
  (countof(array) - 1)
