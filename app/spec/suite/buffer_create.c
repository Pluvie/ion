#include "buffer_create.h"

spec( buffer_create ) {
  argument(uint capacity);
  returns(struct buffer result);

  capacity = 17;
  result = buffer_create(capacity);

  must("return an buffer with requested capacity");
    verify(result.capacity == capacity);

  success();
}
