#include "../spec.h"

static struct {
  void* unused;
} sim;

static struct buffer initialized_buffer;

/* Creates a spec-specific copy of the function so that the linker does not find
  multiple definitions of this function with the same name. */
#define buffer_push     specced__buffer_push
#include <ion/functions/buffer_push.c>
