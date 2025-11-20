#include "buffer_pointer.h"

spec( buffer_pointer ) {
  argument(struct buffer* allocator);
  returns(void* result);

  precondition("a valid, previously initialized buffer allocator");
  #define preconditions \
    initialized_allocator = buffer_create(64); \
    initialized_allocator.position = 32; \
    allocator = &initialized_allocator;

  apply(preconditions);
  result = buffer_pointer(allocator);

  must("return a pointer to the allocator data at its current position");
    verify(result == ((byte*) allocator->data) + allocator->position);

  success();
  end();
}
