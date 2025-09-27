unsigned int bit_count_leading_ones (
    unsigned int value
)
{
/*
  If C standard is C23 and up, the stdc_leading_* functions can be used.
  If not, resorts to using the compiler builtins.
*/
#if   INT_BIT_WIDTH == 64
  #if __STDC_VERSION__ <= 201711L   /* C17 */
    return __builtin_popcountll(value);
  #else
    return stdc_leading_ones_ull(value);
  #endif
#elif INT_BIT_WIDTH == 32
  #if __STDC_VERSION__ <= 201711L   /* C17 */
    return __builtin_popcountl(value);
  #else
    return stdc_leading_ones_ul(value);
  #endif
#endif
}
