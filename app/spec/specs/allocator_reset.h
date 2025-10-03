#include "../spec.h"

/*
  Creates a spec-specific copy of the function so that the linker does not find
  multiple definitions of this function with the same name.
*/
#define allocator_reset     specced__allocator_reset
#include <ion/functions/allocator_reset.c>
