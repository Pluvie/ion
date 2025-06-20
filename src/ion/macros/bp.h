/**
 * Helper to print a boolean value in a printf-like function.
 *
 * Example:
 *
 * ```c
 * bool value = true;
 * printf("Value: %s\n", bp(value));
 * ```
 */
#define bp(val) \
  ((val) ? "true" : "false")
