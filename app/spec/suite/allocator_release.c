#include "allocator_release.h"

spec( allocator_release ) {
  argument(struct allocator* allocator);

  precondition("a valid, previously initialized allocator");
  #define preconditions \
    memory_set(&initialized_allocator, 0, sizeof(initialized_allocator)); \
    initialized_allocator.data = (byte*) 0x01; \
    initialized_allocator.regions.count = 3; \
    initialized_allocator.regions.addresses = (void**) &addresses;
    allocator = &initialized_allocator; \

  apply(preconditions);
  allocator_release(allocator);

  must("release the allocator regions");
    verify(sim.released[0] == (void*) 0x02);
    verify(sim.released[1] == (void*) 0x03);
    verify(sim.released[2] == (void*) 0x04);
  must("release the allocator region addresses");
    verify(sim.released[3] == (void*) &addresses);
  must("release the allocator data");
    verify(sim.released[4] == (void*) 0x01);
  must("zero out the allocator struct");
    verify(memory_equal(allocator, &released_allocator, sizeof(*allocator)));

  success();
}
