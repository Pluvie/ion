#include "arena_create.h"

spec( arena_create ) {
  argument(uint capacity);
  returns(struct arena result);

  capacity = 17;
  result = arena_create(capacity);

  must("return an arena allocator with requested capacity");
    verify(result.capacity == capacity);

  success();
}
