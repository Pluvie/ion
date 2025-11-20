#include "buffer_position_set.h"

spec( buffer_position_set ) {
  argument(struct buffer* allocator);
  argument(uint position);

  precondition("a valid, previously initialized buffer allocator");
  #define preconditions \
    initialized_allocator = buffer_create(64); \
    allocator = &initialized_allocator;

  apply(preconditions);
  position = 32;
  buffer_position_set(allocator, position);

  must("set the current allocator position");
    verify(allocator->position == position);

  success();
  end();
}
