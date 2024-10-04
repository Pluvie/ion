/**
 * Allocates a `struct array` with the given *name* on the provided *allocator.*
 *
 * The *name* must be an already existing indentifier.
 *
 * The array has elements all of the given *type*, and can have a provided
 * *initial_capacity*. */
#define array_allocate(name, type, initial_capacity, allocator)     \
  name = memory_alloc(allocator, sizeof(struct array));             \
  *(name) = array_init(sizeof(type), initial_capacity, allocator)
