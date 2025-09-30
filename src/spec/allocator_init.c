#include "allocator_init.h"

spec( allocator_init ) {
  argument(unsigned int capacity);

  when("the capacity is not a power of two") {
    capacity = 17;
    struct allocator result = allocator_init(capacity);

    must("return an allocator with capacity equal to the next power of two");
      verify(result.capacity == next_pow2(capacity));

    success();
  } end();

  when("the capacity is a power of two") {
    capacity = 32;
    struct allocator result = allocator_init(capacity);

    must("return an allocator with the specified capacity");
      verify(result.capacity == capacity);

    success();
  } end();
}
