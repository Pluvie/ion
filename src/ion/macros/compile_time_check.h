/**
 * Check a condition at compile time.
 *
 * Example:
 *
 * ```c
 * compile_time_check(EXAMPLE_CONSTANT == 42,
 *   "the constant EXAMPLE_CONSTANT must be equal to 42");
 * ```
 *
 * If the *condition* evaluates to false, then a compile error is thrown, which prints
 * the provided *message*. */
#define compile_time_check(condition, message) \
  _Static_assert(condition, message)
