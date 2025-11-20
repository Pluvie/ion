#include "buffer_position_get.h"

spec( buffer_position_get ) {
  argument(struct buffer* allocator);
  returns(uint result);

  precondition("a valid, previously initialized buffer allocator");
  #define preconditions \
    initialized_allocator = buffer_create(64); \
    initialized_allocator.position = 32; \
    allocator = &initialized_allocator;

  apply(preconditions);
  result = buffer_position_get(allocator);

  must("return the current allocator position");
    verify(result == allocator->position);

  success();
  end();
}
