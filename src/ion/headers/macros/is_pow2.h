/**
 * Determines if *number* is a power of `2`.
 *
 * If the number is `0` or less, this macro results always in `false`, otherwise it
 * results `true` if the number is a power of `2` and `false` in the other cases. */
#define is_pow2(number) \
  (number > 0 ? (number & (number - 1)) == 0 : false)
