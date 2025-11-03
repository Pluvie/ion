#include "../spec.h"

static struct {
  void* unused;
} sim;

static struct allocator initialized_allocator;

/* Creates a spec-specific copy of the function so that the linker does not find
  multiple definitions of this function with the same name. */
#define allocator_stretch     specced__allocator_stretch
#include <ion/functions/allocator_stretch.c>
