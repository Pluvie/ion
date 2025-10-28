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
