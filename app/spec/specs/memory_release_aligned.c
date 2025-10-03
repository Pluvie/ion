#include "memory_release_aligned.h"

spec( memory_release_aligned ) {
  argument(void* address);

  precondition("a valid, previously acquired aligned memory address");
    #define preconditions \
      unsigned int alignment = 16; \
      address = memory_acquire_aligned(32, alignment); \
      verify(address != nullptr); \
      verify(((unsigned int) address) % alignment == 0);

  apply(preconditions);
  memory_release_aligned(address);

  must("release the acquired memory");
    verify(sim.acquired == nullptr);

  success();

  #undef preconditions
}
