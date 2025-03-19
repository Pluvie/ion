#ifdef ION_INCLUDED
static inline
#endif

struct tensor* tensor_allocate (
    u64 typesize,
    struct vector* input_dimensions,
    struct memory* allocator
);
