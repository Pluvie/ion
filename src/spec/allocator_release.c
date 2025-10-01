#include "allocator_release.h"

spec( allocator_release ) {
  argument(struct allocator* allocator);

  precondition("a valid, previously initialized allocator");
  #define preconditions \
    int addresses[] = { 0x02, 0x03, 0x04 }; \
    struct allocator initialized_allocator = { \
      .data = (void*) 0x01, \
      .regions = { \
        .count = 3, \
        .addresses = (void**) &addresses, \
      } \
    }; \
    allocator = &initialized_allocator; \

  apply(preconditions);
  allocator_release(allocator);

  must("release the allocator data");
    verify(sim.released[0] == (void*) 0x01);
  must("release the allocator regions");
    verify(sim.released[1] == (void*) 0x02);
    verify(sim.released[2] == (void*) 0x03);
    verify(sim.released[3] == (void*) 0x04);
  must("release the allocator region addresses");
    verify(sim.released[4] == (void*) &addresses);
  must("zero out the allocator struct");
    verify(memory_equal(allocator, &(struct allocator) { 0 }, sizeof(*allocator)));

  success();
}
