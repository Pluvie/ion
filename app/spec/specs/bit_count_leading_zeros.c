#include "bit_count_leading_zeros.h"

spec( bit_count_leading_zeros ) {
  argument(unsigned int value);

  must("return the number of leading bits set to zero on the given value");
    {
      value = ~((unsigned int) 0);
      unsigned int result = bit_count_leading_zeros(value);
      verify(result == 0);
    }
    {
      value = ((unsigned int) 1) << 15;
      unsigned int result = bit_count_leading_zeros(value);
      verify(result == INT_BIT_WIDTH - 15 - 1);
    }
    {
      value = (unsigned int) 0;
      unsigned int result = bit_count_leading_zeros(value);
      verify(result == INT_BIT_WIDTH);
    }

  success();
}
