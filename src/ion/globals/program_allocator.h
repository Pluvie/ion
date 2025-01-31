/**
 * Global allocator used by the whole program. Not thread-safe. */
struct memory program_allocator = allocator_init();
