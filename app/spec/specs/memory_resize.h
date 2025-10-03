#include "../framework.h"

static struct {
  void* realloc;
  char* fatal;
} sim = { 0 };

#undef  fatal
#define fatal(msg)    return sim.fatal = msg, nullptr;
#define realloc(...)  sim.realloc

/*
  Creates a spec-specific copy of the function so that the linker does not find
  multiple definitions of this function with the same name.
*/
#define memory_resize   specced__memory_resize
#include <ion/functions/memory_resize.c>
