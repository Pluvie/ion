#include "../spec.h"

static struct buffer initialized_buffer;

/* Creates a spec-specific copy of the function so that the linker does not find
  multiple definitions of this function with the same name. */
#define buffer_position_get     specced__buffer_position_get
#include <ion/functions/buffer_position_get.c>
