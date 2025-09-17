/*
 Calculates the next multiple of a power of 2 starting from *number*.
 If the *number* is already a multiple of a power of 2, this macro is idempotent.
*/
#define next_mul2(number, pow2) \
  (((unsigned int) number + (pow2 - 1)) & ~(pow2 - 1))
