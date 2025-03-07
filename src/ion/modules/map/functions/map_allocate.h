#ifdef ION_INCLUDED
static inline
#endif

struct map* map_allocate (
    u64 key_typesize,
    u64 value_typesize,
    u64 initial_capacity,
    struct memory* allocator
)
/**
 * ### Description
 *
 * Allocates a `struct map` with the given *initial_capacity* on the provided
 * *allocator.*
 *
 * The map has keys all of the given *key_typesize* and values all of the given
 * *value_typesize*.
 *
 * ### Return Value
 *
 * The allocated map.
 *
 */;
