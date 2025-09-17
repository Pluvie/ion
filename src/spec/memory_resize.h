#include "../ion/functions/fatal.c"
#include "../ion/functions/memory_acquire.c"
#include "../ion/functions/memory_release.c"

#define memory_resize   specced__memory_resize
#include "spec_framework.h"

static struct {
  void* realloc;
  char* fatal;
} sim = { 0 };

#define realloc(...)  sim.realloc
#define fatal(msg)    return sim.fatal = msg, nullptr;

#include "../ion/functions/memory_resize.c"

#undef  realloc
#undef  fatal
