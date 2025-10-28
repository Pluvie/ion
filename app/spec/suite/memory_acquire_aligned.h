#include "../spec.h"

static struct {
  char* fatal;
  bool allocation_fails;
} sim;

#undef  fatal
#define fatal(msg)  return sim.fatal = msg, nullptr;

#if standard(>= C11)
#define aligned_alloc(align, amount) \
  sim.allocation_fails ? nullptr : (void*) (10*alignment)

#else
#define malloc(amount) \
  sim.allocation_fails ? nullptr : (void*) 0x01

#define memory_set(target, value, length)
#endif

/* Creates a spec-specific copy of the function so that the linker does not find
  multiple definitions of this function with the same name. */
#define memory_acquire_aligned  specced__memory_acquire_aligned
#include <ion/functions/memory_acquire_aligned.c>

/* Restore the original memory set behaviour. */
#ifdef  memory_set
#undef  memory_set
#endif
