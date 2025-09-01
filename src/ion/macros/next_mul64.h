/**
 * Calculates the next multiple of 64 starting from *number*.
 *
 * If the *number* is already a multiple of 64, this macro is idempotent. */
#define next_mul64(number) \
  (((int) number + 63) & (~63))
