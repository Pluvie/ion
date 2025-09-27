unsigned int bit_count_leading_ones (
    unsigned int value
)
{
#if   INT_BIT_WIDTH == 64
  #if __has_include(<stdbit.h>)
    return stdc_leading_ones_ull(value);
  #else
    return __builtin_popcountll(value);
  #endif
#elif INT_BIT_WIDTH == 32
  #if __has_include(<stdbit.h>)
    return stdc_leading_ones_ul(value);
  #else
    return __builtin_popcountl(value);
  #endif
#endif
}
