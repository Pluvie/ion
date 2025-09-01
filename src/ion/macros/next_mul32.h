/**
 * Calculates the next multiple of 32 starting from *number*.
 *
 * If the *number* is already a multiple of 32, this macro is idempotent. */
#define next_mul32(number) \
  (((int) number + 31) & (~31))
