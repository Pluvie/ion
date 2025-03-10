#include "../../src/ion.h"
#include "../../src/ion.c"

i32 example_sum (
    i32 numbers_length,
    i32 *numbers
)
{
  i32 sum = 0;

  for (i32 i = 0; i < numbers_length; i++)
    sum += numbers[i];

  return sum;
}
