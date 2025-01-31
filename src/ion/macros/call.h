/**
 * Wraps a function call with automatic error checking. Should be used with
 * curly brackets to help readability. Example:
 *
 * ```c
 * call(printf, "Lucky Number: %i", 7) {
 *   // An error occurred in printf, but we ignore it.
 * }
 *
 * call(important_function, var1, var2) {
 *   log(FATAL, "An important function failed!");
 *   return EXIT_FAILURE;
 * }
 * ```
 *
 * */
#define call(function, ...)                     \
  function(##__VA_ARGS__); if (error.occurred)
