#include "../spec.h"

/* Creates a spec-specific copy of the function so that the linker does not find
  multiple definitions of this function with the same name. */
#define buffer_create specced__buffer_create
#include <ion/functions/buffer_create.c>
