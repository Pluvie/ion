#include "../spec.h"

static struct {
  void* unused;
} sim;

/* Creates a spec-specific copy of the function so that the linker does not find
  multiple definitions of this function with the same name. */
#define memory_compare specced__memory_compare
#include <ion/functions/memory_compare.c>
