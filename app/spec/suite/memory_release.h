#include "../spec.h"

static struct {
  void* acquired;
} sim = { 0 };

#define memory_acquire(amount)  (sim.acquired = (void*) 0x50);
#define free(address)           (sim.acquired = nullptr);

/* Creates a spec-specific copy of the function so that the linker does not find
  multiple definitions of this function with the same name. */
#define memory_release specced__memory_release
#include <ion/functions/memory_release.c>
