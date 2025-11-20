#include "buffer_pointer_at.h"

spec( buffer_pointer_at ) {
  argument(struct buffer* allocator);
  argument(uint position);
  returns(void* result);

  precondition("a valid, previously initialized buffer allocator");
  #define preconditions \
    initialized_allocator = buffer_create(64); \
    initialized_allocator.position = 48; \
    allocator = &initialized_allocator;

  when("the position is lesser than the allocator position") {
    apply(preconditions);
    position = 32;
    result = buffer_pointer_at(allocator, position);

    must("return a pointer to the allocator data at the requested position");
      verify(result == ((byte*) allocator->data) + position);

    success();
  } end();

  when("the position is not lesser than the allocator position") {
    apply(preconditions);
    position = 92;
    result = buffer_pointer_at(allocator, position);

    must("fatally fail with a specific message");
      verify(cstr_equal(sim.fatal, "buffer overflow"));

    success();
  } end();
}
