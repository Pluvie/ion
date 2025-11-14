#include "../spec.h"

static struct buffer initialized_buffer;

static struct {
  char* fatal;
} sim = { 0 };

#define fatal(msg)  return sim.fatal = msg, nullptr;

/* Creates a spec-specific copy of the function so that the linker does not find
  multiple definitions of this function with the same name. */
#define buffer_address_at     specced__buffer_address_at
#include <ion/functions/buffer_address_at.c>
