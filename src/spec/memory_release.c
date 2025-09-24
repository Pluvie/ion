#include "memory_release.h"

spec( memory_release ) {
  argument(void* address);

  precondition("a valid, previously acquired memory address");
    #define preconditions \
      address = memory_acquire(32); \
      verify(address != nullptr);

  apply(preconditions);
  memory_release(address);

  must("release the acquired memory");
    verify(sim.acquired == nullptr);

  success();

  #undef preconditions
}

#undef memory_release
