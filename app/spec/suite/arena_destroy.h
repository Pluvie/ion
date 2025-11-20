#include "../spec.h"

static struct {
  int count;
  void* released[5];
} sim;

static struct arena initialized_allocator;
static struct arena zeroed_out_allocator = { 0 };
static int addresses[] = { 0x02, 0x03, 0x04 };

#define memory_release(address) \
  sim.released[sim.count++] = (void*) address;

/* Creates a spec-specific copy of the function so that the linker does not find
  multiple definitions of this function with the same name. */
#define arena_destroy specced__arena_destroy
#include <ion/functions/arena_destroy.c>
