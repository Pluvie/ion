void* memory_acquire (
    uint amount
);

void* memory_acquire_aligned (
    uint amount,
    uint alignment
);

int memory_compare (
    void* m1,
    void* m2,
    uint size
);

void* memory_copy (
    void* target,
    void* source,
    uint amount
);

bool memory_equal (
    void* m1,
    void* m2,
    uint size
);

void memory_release (
    void* address
);

void memory_release_aligned (
    void* aligned_address
);

void* memory_resize (
    void* address,
    uint amount
);

void* memory_set (
    void* target,
    byte value,
    uint amount
);
