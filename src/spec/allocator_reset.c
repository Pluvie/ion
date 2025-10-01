#include "allocator_reset.h"

spec( allocator_reset ) {
  argument(struct allocator* allocator);

  precondition("a valid, previously initialized allocator");
  #define preconditions \
    struct allocator initialized_allocator = allocator_init(64); \
    allocator = &initialized_allocator;

  apply(preconditions);
  allocator_reset(allocator);

  must("reset the allocator position to 0");
    verify(allocator->position == 0);

  success();
}
