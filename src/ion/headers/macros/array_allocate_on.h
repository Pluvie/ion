/**
 * Allocates a `struct array` with the given *name* on the provided *allocator.*
 *
 * The array has elements all of the given *type*, and can have a provided
 * *initial_capacity*. */
#define array_allocate_on(allocator, name, type, initial_capacity)    \
  struct array* name = memory_alloc(allocator, sizeof(struct array)); \
  *name = array_init(sizeof(type), initial_capacity, allocator)
