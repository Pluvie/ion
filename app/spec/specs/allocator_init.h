#include "../framework.h"

static struct {
  void* unused;
} sim;

/*
  Creates a spec-specific copy of the function so that the linker does not find
  multiple definitions of this function with the same name.
*/
#define allocator_init    specced__allocator_init
#include <ion/functions/allocator_init.c>
