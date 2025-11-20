#include "buffer_destroy.h"

spec( buffer_destroy ) {
  argument(struct buffer* allocator);

  precondition("a valid, previously initialized buffer allocator");
  #define preconditions \
    memory_set(&initialized_allocator, 0, sizeof(initialized_allocator)); \
    initialized_allocator.data = (byte*) 0x01; \
    allocator = &initialized_allocator;

  apply(preconditions);
  buffer_destroy(allocator);

  must("release the allocator data");
    verify(sim.released[0] == (void*) 0x01);
  must("zero out the allocator struct");
    verify(memory_equal(allocator, &zeroed_out_allocator, sizeof(*allocator)));

  success();
}
