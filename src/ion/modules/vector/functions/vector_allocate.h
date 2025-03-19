#ifdef ION_INCLUDED
static inline
#endif

struct vector* vector_allocate (
    u64 typesize,
    u64 length,
    struct memory* allocator
);
