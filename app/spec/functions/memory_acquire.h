#include "../framework.h"

static struct {
  void* malloc;
  char* fatal;
} sim = { 0 };

#undef  fatal
#define fatal(msg)    return sim.fatal = msg, nullptr;
#define malloc(...)   sim.malloc

/*
  Creates a spec-specific copy of the function so that the linker does not find
  multiple definitions of this function with the same name.
*/
#define memory_acquire    specced__memory_acquire
#include <ion/functions/memory_acquire.c>
