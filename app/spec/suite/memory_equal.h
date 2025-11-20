#include "../spec.h"

static struct {
  void* unused;
} sim;

/* Creates a spec-specific copy of the function so that the linker does not find
  multiple definitions of this function with the same name. */
#define memory_equal specced__memory_equal
#include <ion/functions/memory_equal.c>
