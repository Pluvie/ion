#include "bit_count_leading_zeros.h"

spec( bit_count_leading_zeros ) {
  argument(uint value);
  returns(uint result);

  must("return the number of leading bits set to zero on the given value");
    {
      value = ~((uint) 0);
      result = bit_count_leading_zeros(value);
      verify(result == 0);
    }
    {
      value = ((uint) 1) << 15;
      result = bit_count_leading_zeros(value);
      verify(result == INT_BITSIZE - 15 - 1);
    }
    {
      value = (uint) 0;
      result = bit_count_leading_zeros(value);
      verify(result == INT_BITSIZE);
    }

  success();
}
