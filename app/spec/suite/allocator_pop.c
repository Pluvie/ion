#include "allocator_pop.h"

spec( allocator_pop ) {
  argument(struct allocator* allocator);
  argument(uint amount);
  returns(void* result);

  precondition("a valid, previously initialized allocator");
  #define preconditions \
    struct allocator initialized_allocator = allocator_init(64); \
    allocator = &initialized_allocator;

  when("the amount is not greater than the allocator position") {
    apply(preconditions);
    amount = 24;
    allocator->position = 32;
    result = allocator_pop(allocator, amount);

    must("decrease the allocator position by the given amount");
      verify(allocator->position == 32 - 24);
    must("return a pointer to the allocator data offset");
      verify(result == allocator->data + allocator->position);

    success();
  } end();

  when("the amount is greater than the allocator position") {
    apply(preconditions);
    amount = 48;
    allocator->position = 32;
    result = allocator_pop(allocator, amount);

    must("set the allocator position to 0");
      verify(allocator->position == 0);
    must("return a pointer to the allocator data");
      verify(result == allocator->data);

    success();
  } end();
}
