unsigned int bit_count_leading_ones (
    unsigned int value
)
{
#if   INT_BIT_WIDTH == 64
  return stdc_leading_ones_ull(value);
#elif INT_BIT_WIDTH == 32
  return stdc_leading_ones_ul(value);
#elif INT_BIT_WIDTH == 16
  return stdc_leading_ones_ui(value);
#endif
}
