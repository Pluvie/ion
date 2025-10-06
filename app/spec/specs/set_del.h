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
#define _del    _del_specced
#include <ion/containers/set/functions/set_del.c>

/*
  Redefines the `set_del` macro to point to the specced function.
*/
#undef  set_del
#define set_del(l,e) \
  set<T>_del_specced(l, e)
