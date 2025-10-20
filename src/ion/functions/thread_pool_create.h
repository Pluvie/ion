struct thread_pool* thread_pool_create (
    unsigned int threads_capacity
);

static void thread_main_loop (
    struct thread_pool* pool
);
