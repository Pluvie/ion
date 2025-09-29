#include "spec_framework.h"

static struct {
  char* fatal;
  struct {
    void* result;
    unsigned int alignment;
  } aligned_alloc;
} sim = { 0 };

#undef  fatal
#define fatal(msg)  return sim.fatal = msg, nullptr;
#define aligned_alloc(align, ...) \
  sim.aligned_alloc.result; sim.aligned_alloc.alignment = align;

/*
  Creates a spec-specific copy of the function so that the linker does not find
  multiple definitions of this function with the same name.
*/
#define memory_acquire_aligned  specced__memory_acquire_aligned
#include "../ion/functions/memory_acquire_aligned.c"
