unsigned int bit_count_leading_zeros (
    unsigned int value
)
{
#if   INT_BIT_WIDTH == 64
  #if __has_include(<stdbit.h>)
    return stdc_leading_zeros_ull(value);
  #else
    return __builtin_clzll(value);
  #endif
#elif INT_BIT_WIDTH == 32
  #if __has_include(<stdbit.h>)
    return stdc_leading_zeros_ul(value);
  #else
    return __builtin_clzl(value);
  #endif
#endif
}
