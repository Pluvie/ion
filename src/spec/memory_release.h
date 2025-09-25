#include "spec_framework.h"

static struct {
  void* acquired;
} sim = { 0 };

#define memory_acquire(...)   (sim.acquired = (void*) 0x50);
#define free(...)             (sim.acquired = nullptr);

/*
  Creates a spec-specific copy of the function so that the linker does not find
  multiple definitions of this function with the same name.
*/
#define memory_release  specced__memory_release
#include "../ion/functions/memory_release.c"
