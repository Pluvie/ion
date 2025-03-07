#ifdef ION_INCLUDED
static inline
#endif

struct array* array_allocate (
    u64 typesize,
    u64 initial_capacity,
    struct memory* allocator
)
/**
 * ### Description
 *
 * Allocates a `struct array` with the given *initial_capacity* on the provided
 * *allocator.*
 *
 * The array has elements all of the given *typesize*.
 *
 * ### Return Value
 *
 * The allocated array.
 *
 */;
