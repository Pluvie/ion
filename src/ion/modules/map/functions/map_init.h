#ifdef ION_INCLUDED
static inline
#endif

struct map map_init (
    u64 key_typesize,
    u64 value_typesize,
    u64 initial_capacity,
    struct memory* allocator
);
