#define memory_release  specced__memory_release
#include "spec_framework.h"

static struct {
  void* acquired;
} sim = { 0 };

#define memory_acquire(...)   (sim.acquired = (void*) 0x50);
#define free(...)             (sim.acquired = nullptr);

#include "../ion/functions/memory_release.c"

#undef  free
