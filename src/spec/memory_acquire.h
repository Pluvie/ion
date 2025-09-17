#define memory_acquire    specced__memory_acquire
#include "spec_framework.h"

static struct {
  void* malloc;
  char* fatal;
} sim = { 0 };

#define malloc(...)   sim.malloc
#define fatal(msg)    return sim.fatal = msg, nullptr;

#include "../ion/functions/memory_acquire.c"

#undef  malloc
#undef  fatal
