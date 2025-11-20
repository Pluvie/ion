#include "../spec.h"

static struct {
  void* unused;
} sim;

static struct arena initialized_allocator;

/* Creates a spec-specific copy of the function so that the linker does not find
  multiple definitions of this function with the same name. */
#define arena_push specced__arena_push
#include <ion/functions/arena_push.c>
