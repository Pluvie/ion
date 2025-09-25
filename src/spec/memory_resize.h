/*
  Adds required dependencies for this translation unit.
*/
#include "../ion/functions/fatal.c"
#include "../ion/functions/memory_acquire.c"
#include "../ion/functions/memory_release.c"

#include "spec_framework.h"

static struct {
  void* realloc;
  char* fatal;
} sim = { 0 };

#define realloc(...)  sim.realloc
#define fatal(msg)    return sim.fatal = msg, nullptr;

/*
  Creates a spec-specific copy of the function so that the linker does not find
  multiple definitions of this function with the same name.
*/
#define memory_resize   specced__memory_resize
#include "../ion/functions/memory_resize.c"
