#include "../spec.h"
#include "../containers.h"

static struct {
  char* fatal;
} sim;

#undef  fatal
#define fatal(msg)  sim.fatal = msg

/*
  Creates a spec-specific copy of the function so that the linker does not find
  multiple definitions of this function with the same name.
*/
#define T       char*
#define _add    _add_specced
#include <ion/containers/set/functions/set_add.c>

/*
  Redefines the `set_add` macro to point to the specced function.
*/
#undef  set_add
#define set_add(s, e) \
  set<T>_add_specced(s, e)
