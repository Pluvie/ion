#include "allocator_pop.h"

spec( allocator_pop ) {
  argument(struct allocator* allocator);
  argument(uint amount);
  returns(void* result);

  precondition("a valid, previously initialized allocator");
  #define preconditions \
    struct allocator initialized_allocator = allocator_init(64); \
    allocator = &initialized_allocator;

  when("the amount is not greater than the arena position") {
    apply(preconditions);
    amount = 24;
    allocator->arena.position = 32;
    result = allocator_pop(allocator, amount);

    must("decrease the arena position by the given amount");
      verify(allocator->arena.position == 32 - 24);
    must("return a pointer to the arena data offset");
      verify(result == allocator->arena.data + allocator->arena.position);

    success();
  } end();

  when("the amount is greater than the arena position") {
    apply(preconditions);
    amount = 48;
    allocator->arena.position = 32;
    result = allocator_pop(allocator, amount);

    must("set the arena position to 0");
      verify(allocator->arena.position == 0);
    must("return a pointer to the arena data");
      verify(result == allocator->arena.data);

    success();
  } end();
}
