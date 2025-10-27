#include <ion.h>
#include <ion/spec.h>

static struct {
  void* unused;
} sim;

static struct allocator initialized_allocator;

/* Creates a spec-specific copy of the function so that the linker does not find
  multiple definitions of this function with the same name. */
#define allocator_push    specced__allocator_push
#include <ion/functions/allocator_push.c>
