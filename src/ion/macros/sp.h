/**
 * Helper to print a string on a printf-like function.
 *
 * Example:
 *
 * ```c
 * string message = s("Hello World!");
 * printf("Message: %.*s\n", sp(message));
 * ```
 */
#define sp(str) \
  (int32) (str).length, (char*) (str).pointer
