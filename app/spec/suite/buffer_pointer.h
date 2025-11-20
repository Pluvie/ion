#include "../spec.h"

static struct buffer initialized_allocator;

/* Creates a spec-specific copy of the function so that the linker does not find
  multiple definitions of this function with the same name. */
#define buffer_pointer specced__buffer_pointer
#include <ion/functions/buffer_pointer.c>
