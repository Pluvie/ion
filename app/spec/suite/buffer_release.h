#include "../spec.h"

static struct {
  int count;
  void* released[1];
} sim;

static struct buffer initialized_buffer;
static struct buffer released_buffer = { 0 };

#define memory_release(address)   sim.released[sim.count++] = (void*) address;

/* Creates a spec-specific copy of the function so that the linker does not find
  multiple definitions of this function with the same name. */
#define buffer_release     specced__buffer_release
#include <ion/functions/buffer_release.c>
