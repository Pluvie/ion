#include "../spec.h"

/* Creates a spec-specific copy of the function so that the linker does not find
  multiple definitions of this function with the same name. */
#define arena_create specced__arena_create
#include <ion/functions/arena_create.c>
