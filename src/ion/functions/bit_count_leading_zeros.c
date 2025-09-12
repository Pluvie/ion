unsigned int bit_count_leading_zeros (
    unsigned int value
)
{
#if   INT_BIT_WIDTH == 64
  return stdc_leading_zeros_ull(value);
#elif INT_BIT_WIDTH == 32
  return stdc_leading_zeros_ul(value);
#elif INT_BIT_WIDTH == 16
  return stdc_leading_zeros_us(value);
#endif
}
