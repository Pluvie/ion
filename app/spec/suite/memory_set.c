#include "memory_set.h"

spec( memory_set ) {
  argument(void* target);
  argument(byte value);
  argument(uint amount);
  returns(void* result);

  precondition("a valid memory region");
    #define preconditions \
      byte region[8] = { 1, 1, 1, 1, 1, 1, 1, 1 };

  {
    apply(preconditions);
    target = region;
    value = 2;
    amount = 4;
    result = memory_set(target, value, amount);

    must("set the first amount of bytes of target with the given byte value");
      verify(region[0] == 2);
      verify(region[1] == 2);
      verify(region[2] == 2);
      verify(region[3] == 2);
      verify(region[4] == 1);
      verify(region[5] == 1);
      verify(region[6] == 1);
      verify(region[7] == 1);
    must("return a pointer to the target");
      verify(result == target);

    success();
  }
}
