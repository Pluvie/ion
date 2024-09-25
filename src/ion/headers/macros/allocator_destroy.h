/**
 * Destroys and releases all memory used by the allocator with the given *name*. */
#define allocator_destroy(name) \
  memory_release(name);         \
  free(name)
