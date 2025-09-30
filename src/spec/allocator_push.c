#include "allocator_push.h"

spec( allocator_push ) {
  argument(struct allocator* allocator);
  argument(unsigned int amount);

  precondition("a valid, previously initialized allocator");
  #define preconditions \
    allocator = allocator_init(32);

  when("the allocator has no previous data") {
    when("the amount is not greater than the allocator capacity") {
      amount = 16;
      void* result = allocator_push(amount);

      must("increase the allocator position");
        verify(
      must("return a valid memory address");
        verify(result >= allocator.data && result <= allocator.data + allocator.capacity);

      success();
    } end();
  } end();

  when("the capacity is a power of two") {
    capacity = 32;
    struct allocator result = allocator_push(capacity);

    must("return an allocator with the specified capacity");
      verify(result.capacity == capacity);

    success();
  } end();
}
