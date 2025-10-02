#include "../framework.h"

static struct {
  char* fatal;
  bool allocation_fails;
} sim;

#undef  fatal
#define fatal(msg)  return sim.fatal = msg, nullptr;

#if standard(>= C11)
#define aligned_alloc(align, ...) \
  sim.allocation_fails ? nullptr : (void*) (10*alignment)

#else
#define malloc(...) \
  sim.allocation_fails ? nullptr : (void*) 0x01

#define memory_set(...)
#endif

/*
  Creates a spec-specific copy of the function so that the linker does not find
  multiple definitions of this function with the same name.
*/
#define memory_acquire_aligned  specced__memory_acquire_aligned
#include <ion/functions/memory_acquire_aligned.c>
