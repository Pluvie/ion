#include "../framework.h"

static struct {
  void* acquired;
} sim = { 0 };

#define memory_acquire_aligned(...) (sim.acquired = (void*) 0x80);

#if standard(>= C11)
#undef  aligned_free
#define aligned_free(...)   (sim.acquired = nullptr);
#else
#define free(...)           (sim.acquired = nullptr);
#endif

/*
  Creates a spec-specific copy of the function so that the linker does not find
  multiple definitions of this function with the same name.
*/
#define memory_release_aligned  specced__memory_release_aligned
#include <ion/functions/memory_release_aligned.c>
