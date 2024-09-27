/**
 * Thread local allocator used by the fibers. Thread-safe. */
__thread struct memory fiber_allocator = allocator_init();
