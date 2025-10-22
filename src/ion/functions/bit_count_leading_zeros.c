unsigned int bit_count_leading_zeros (
    unsigned int value
)
{
/*
  If C standard is C23 and up, the stdc_leading_* functions can be used.
  If not, resorts to using the compiler builtins.
*/
#if standard(>= C23)
  #if   INT_BIT_WIDTH == 64
    return stdc_leading_zeros_ull(value);
  #elif INT_BIT_WIDTH == 32
    return stdc_leading_zeros_ul(value);
  #endif
#else
  #if compiler(GCC) || compiler(CLANG)
    if (value == 0)
      return INT_BIT_WIDTH;

    #if   INT_BIT_WIDTH == 64
      return __builtin_clzll(value);
    #elif INT_BIT_WIDTH == 32
      return __builtin_clzl(value);
    #endif

  #elif compiler(MSVC)
    /* See the [intrinsic definition](
      https://learn.microsoft.com/en-us/cpp/intrinsics/bitscanreverse-bitscanreverse64?view=msvc-170)
      The `uint0` type captures the `unsigned long * Index` argument. */
    uint0 count = 0;
    #if   INT_BIT_WIDTH == 64
      unsigned char scan = _BitScanReverse64(&count, value);
    #elif INT_BIT_WIDTH == 32
      unsigned char scan = _BitScanReverse(&count, value);
    #endif
    if (scan == 0)
      return INT_BIT_WIDTH;
    else
      return INT_BIT_WIDTH - count;
  #endif
#endif
}
