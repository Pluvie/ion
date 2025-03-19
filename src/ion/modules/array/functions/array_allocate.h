#ifdef ION_INCLUDED
static inline
#endif

struct array* array_allocate (
    u64 typesize,
    u64 initial_capacity,
    struct memory* allocator
);
