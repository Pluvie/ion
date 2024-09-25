/**
 * Allocates a `struct map` with the given *name* on the provided *allocator.*
 *
 * The map has keys all of the given *key_type*, and values all of the given
 * *value_type*, and can have a provided *initial_capacity*. */
#define map_allocate_on(allocator, name, key_type, value_type, initial_capacity)      \
  struct map* name = memory_alloc(allocator, sizeof(struct map));                     \
  *name = map_init(sizeof(key_type), sizeof(value_type), initial_capacity, allocator)
