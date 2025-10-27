struct allocator allocator_init (
    uint capacity
);

void* allocator_pop (
    struct allocator* allocator,
    uint amount
);

void* allocator_push (
    struct allocator* allocator,
    uint amount
);

void allocator_release (
    struct allocator* allocator
);
