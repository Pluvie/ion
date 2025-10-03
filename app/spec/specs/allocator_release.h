#include "../spec.h"

static struct {
  int count;
  void* released[5];
} sim;

#define memory_release(address)   sim.released[sim.count++] = (void*) address;

/*
  Creates a spec-specific copy of the function so that the linker does not find
  multiple definitions of this function with the same name.
*/
#define allocator_release     specced__allocator_release
#include <ion/functions/allocator_release.c>
