#include "spec_framework.h"

static struct {
  bool aborted;
} sim;

#undef  fatal
#define fatal(...)  specced__print_failure(true __VA_OPT__(,) __VA_ARGS__, nullptr)
#define abort(...)  sim.aborted = true;

/*
  Creates a spec-specific copy of the function so that the linker does not find
  multiple definitions of this function with the same name.
*/
#define print_failure   specced__print_failure
#include "../ion/functions/print_failure.c"
