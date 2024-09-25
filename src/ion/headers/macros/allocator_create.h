/**
 * Creates a new allocator with the given *name* and *initial_capacity*. */
#define allocator_create(name, initial_capacity)        \
  struct memory* name = malloc(sizeof(struct memory));  \
  *name = memory_init(initial_capacity)
