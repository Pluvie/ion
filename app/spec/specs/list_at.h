#include "../spec.h"
#include "../containers.h"

static struct {
  char fatal[128];
} sim;

#undef  fatal
#define fatal(pos, msg) \
  { \
    prints(sim.fatal, sizeof(sim.fatal), pos, msg); \
    return nullptr; \
  }

/*
  Creates a spec-specific copy of the function so that the linker does not find
  multiple definitions of this function with the same name.
*/
#define T       int
#define _at     _at_specced
#include <ion/containers/list/functions/list_at.c>

/*
  Redefines the `list_at` macro to point to the specced function.
*/
#undef  list_at
#define list_at(l, e) \
  list<T>_at_specced(l, e)
