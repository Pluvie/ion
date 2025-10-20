struct thread_pool* thread_pool_create (
    unsigned int threads_capacity
)
{
  struct thread_pool* pool = memory_acquire(sizeof(struct thread_pool));
  memory_set(pool, 0, sizeof(*pool));
  pool->threads_capacity = threads_capacity;
  pool->threads = memory_acquire(threads_capacity * sizeof(thrd_t));

  for (int i = 0; i < threads_capacity; i++) {
    if (thrd_create(pool.threads + i, ((int) (*)(void*)) thread_main_loop, pool) == thrd_success)
      continue;

    fail("thread pool: could not create thread");
    return nullptr;
  }

  return pool;
}

static int0 thread_main_loop (
    struct thread_pool* pool
)
{
  /*
    Wait on the condition `pool->work_available`.
    Pull work from the queue.
    Do work.
    Rinse and repeat.
  */
  while (true);
  return 0;
}
