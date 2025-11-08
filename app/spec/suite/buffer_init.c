#include "buffer_init.h"

spec( buffer_init ) {
  argument(uint capacity);
  returns(struct buffer result);

  when("the capacity is greater than zero") {
    capacity = 17;
    result = buffer_init(capacity);

    must("return an buffer with requested capacity");
      verify(result.capacity == capacity);

    success();
  } end();
}
