uint bit_count_leading_ones (
    uint value
)
{
/* If C standard is C23 and up, the `stdc_leading_*` functions can be used.
  If not, resorts to using the compiler builtins. */
#if standard(>= C23)
#if   INT_BITSIZE == 64
  return stdc_leading_ones_ull(value);
#elif INT_BITSIZE == 32
  return stdc_leading_ones_ul(value);
#endif

#else
  /* There is no compiler builtin to count leading ones, so we count the leading
    zeros of the bit-negated value. */
  if (value == 0)
    return 0;

  return bit_count_leading_zeros(~value);
#endif
}

uint bit_count_leading_zeros (
    uint value
)
{
/* If C standard is C23 and up, the `stdc_leading_*` functions can be used.
  If not, resorts to using the compiler builtins. */
#if standard(>= C23)
#if   INT_BITSIZE == 64
  return stdc_leading_zeros_ull(value);
#elif INT_BITSIZE == 32
  return stdc_leading_zeros_ul(value);
#endif

#else
#if compiler(GCC) || compiler(CLANG)
  if (value == 0)
    return INT_BITSIZE;

  #if   INT_BITSIZE == 64
    return __builtin_clzll(value);
  #elif INT_BITSIZE == 32
    return __builtin_clzl(value);
  #endif

#elif compiler(MSVC)
  /* See the [intrinsic definition](
    https://learn.microsoft.com/en-us/cpp/intrinsics/bitscanreverse-bitscanreverse64?view=msvc-170)
    The `uint_t` type captures the `unsigned long * Index` argument. */
  uint_t count = 0;
#if   INT_BITSIZE == 64
  byte scan = _BitScanReverse64(&count, value);
#elif INT_BITSIZE == 32
  byte scan = _BitScanReverse(&count, value);
#endif

  if (scan == 0)
    return INT_BITSIZE;
  else
    return INT_BITSIZE - count;
#endif
#endif
}
