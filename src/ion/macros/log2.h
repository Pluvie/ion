/*
 Computes the logarithm in base 2 of a *number*.
 
 If the number is negative, 0, 1, the macro returns 0.
 Otherwise returns the calculated logarithm in base 2 of *number*.
 
 The computation is done using compiler bit manipulation primitives, which are fast and
 efficient operation on CPU registers. In this case the primitive is `bit_clz` which
 counts the number of leading zeros in the bit representation of the number.
*/
#define log2(number) \
  ((int) number > 1 ? INT_BIT_WIDTH - bit_count_leading_zeros((unsigned int) number - 1) : 0)
