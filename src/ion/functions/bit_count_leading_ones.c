unsigned int bit_count_leading_ones (
    unsigned int value
)
{
/*
  If C standard is C23 and up, the stdc_leading_* functions can be used.
  If not, resorts to using the compiler builtins.
*/
#if standard(>= C23)
  #if   INT_BIT_WIDTH == 64
    return stdc_leading_ones_ull(value);
  #elif INT_BIT_WIDTH == 32
    return stdc_leading_ones_ul(value);
  #endif
#else
  /*
    There is no compiler builtin to count leading ones, so we first check if there
    are any leading zeros. If this value is greater than zero, then the number starts
    with at least one zero, therefore the number of leading ones is 0. Otherwise,
    utilizes the __builtin_clrsb, which counts the redundant bits after the first, i.e.
    the bits with the same value as the most significant one. This value, plus 1, is
    therefore the number of leading ones.
  */
  #if   INT_BIT_WIDTH == 64
    return __builtin_ctzll(value) > 0 ? 0 : __builtin_clrsbll(value) + 1;
  #elif INT_BIT_WIDTH == 32
    return __builtin_ctzl(value)  > 0 ? 0 : __builtin_clrsbl(value) + 1;
  #endif
#endif
}
