#include "../spec.h"

/* Creates a spec-specific copy of the function so that the linker does not find
  multiple definitions of this function with the same name. */
#define memory_set  specced__memory_set
#include <ion/functions/memory_set.c>
