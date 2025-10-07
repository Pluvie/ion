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

  The specced function here is actually `set_add` and not `map_set`, as the latter is
  just a wrapper on the former.
*/
#define T       char*
#define _add    _add_specced_map
#include <ion/containers/set/functions/set_add.c>

#define K       char*
#define V       int
#define _set    _set_specced
#define set_char_p_int_add  set_char_p_int_add_specced_map
#include <ion/containers/map/functions/map_set.c>

/*
  Redefines the `map_set` macro to point to the specced function.
*/
#undef  map_set
#define map_set(l, k, v) \
  map<K, V>_set_specced(l, k, v)
