/**
 * Calculates the next power of 2 starting from *number*.
 *
 * If the *number* is already a power of 2, this macro is idempotent. */
#define next_pow2(number) \
  ((u64) 1 << log2(number))
