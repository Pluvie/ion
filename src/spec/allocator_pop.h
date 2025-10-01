#include "spec_framework.h"

static struct {
  void* unused;
} sim;

/*
  Creates a spec-specific copy of the function so that the linker does not find
  multiple definitions of this function with the same name.
*/
#define allocator_pop     specced__allocator_pop
#include "../ion/functions/allocator_pop.c"
