static int0 thread_main_loop (
    void* pool_ptr
);

struct thread_pool* thread_pool_create (
    unsigned int threads_capacity
)
{
  struct thread_pool* pool = memory_acquire(sizeof(struct thread_pool));
  memory_set(pool, 0, sizeof(*pool));
  pool->threads_capacity = threads_capacity;
  pool->threads = memory_acquire(threads_capacity * sizeof(thrd_t));

  if (mtx_init(&(pool->work_sync), mtx_plain) != thrd_success) {
    fail("thread pool: could not create mutex");
    return nullptr;
  }

  if (cnd_init(&(pool->work_available)) != thrd_success) {
    fail("thread pool: could not create condition");
    return nullptr;
  }

  for (int i = 0; i < threads_capacity; i++) {
    if (thrd_create(pool->threads + i, thread_main_loop, pool) != thrd_success) {
      fail("thread pool: could not create thread");
      return nullptr;
    }

    if (thrd_detach(pool->threads[i]) != thrd_success) {
      fail("thread pool: could not detach thread");
      return nullptr;
    }
  }

  return pool;
}

static int0 thread_main_loop (
    void* pool_ptr
)
{
  //struct thread_pool* pool = pool_ptr;
  /*
    Wait on the condition `pool->work_available`.
    Pull work from the queue.
    Do work.
    Rinse and repeat.
  */
  //while (true);
  printl("thread started");
  thrd_exit(0);
}
