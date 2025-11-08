#include "../spec.h"

static struct {
  void* unused;
} sim;

/* Creates a spec-specific copy of the function so that the linker does not find
  multiple definitions of this function with the same name. */
#define buffer_pop    specced__buffer_pop
#include <ion/functions/buffer_pop.c>
