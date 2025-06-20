/**
 * Computes the number of elements of a stack allocated array.
 *
 * Example:
 *
 * ```c
 * u64 numbers[11];
 * countof(numbers); // 11, because sizeof(numbers) = 88, sizeof(u64) = 8, 88 / 8 = 11
 * ```
 *
 * This macro does not work with pointer types. The argument must be a stack allocated
 * array, with fixed length. */
#define countof(...) \
  (sizeof(__VA_ARGS__) / sizeof(*(__VA_ARGS__)))
