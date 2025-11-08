#include "allocator_init.h"

spec( allocator_init ) {
  argument(uint capacity);
  returns(struct allocator result);

  when("the capacity is greater than zero") {
    capacity = 17;
    result = allocator_init(capacity);

    must("return an allocator with requested capacity");
      verify(result.capacity == capacity);

    success();
  } end();
}
