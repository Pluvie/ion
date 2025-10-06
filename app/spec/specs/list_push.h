#include "../spec.h"
#include "../containers.h"

static struct {
  char* fatal;
} sim;

#undef  fatal
#define fatal(msg)    return sim.fatal = msg, 0;

/*
  Creates a spec-specific copy of the function so that the linker does not find
  multiple definitions of this function with the same name.
*/
#define T       int
#define _push   _push_specced
#include <ion/containers/list/functions/list_push.c>

/*
  Redefines the list push macro to point to the specced function.
*/
#undef  list_push
#define list_push(l,e) \
  list<T>_push_specced(l, e)
