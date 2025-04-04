#ifdef ION_INCLUDED
static inline
#endif

struct map map_init (
    u32 key_typesize,
    u32 value_typesize,
    u32 initial_capacity,
    struct memory* allocator
);
