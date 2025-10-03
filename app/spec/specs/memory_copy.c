#include "memory_copy.h"

spec( memory_copy ) {
  argument(void* target);
  argument(void* source);
  argument(unsigned int amount);

  precondition("two valid, non overlapping memory regions");
    #define preconditions \
      unsigned char region1[8] = { 1, 1, 1, 1, 1, 1, 1, 1 }; \
      unsigned char region2[8] = { 2, 2, 2, 2, 2, 2, 2, 2 };

  apply(preconditions);
  target = region1;
  source = region2;
  amount = 4;
  void* result = memory_copy(target, source, amount);

  must("copy the source bytes into the target up to the given amount");
    verify(region1[0] == 2);
    verify(region1[1] == 2);
    verify(region1[2] == 2);
    verify(region1[3] == 2);
    verify(region1[4] == 1);
    verify(region1[5] == 1);
    verify(region1[6] == 1);
    verify(region1[7] == 1);
  must("return a pointer to the target");
    verify(result == target);

  success();
}
