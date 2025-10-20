static int0 thread_main_loop (
    void* pool_ptr
);

struct thread_pool* thread_pool_create (
    unsigned int threads_capacity
)
{
  struct thread_pool* pool = memory_acquire(sizeof(struct thread_pool));
  memory_set(pool, 0, sizeof(*pool));
  pool->active = true;
  pool->threads_capacity = threads_capacity;
  pool->threads = memory_acquire(threads_capacity * sizeof(*(pool->threads)));

  if (mtx_init(&(pool->sync), mtx_plain) != thrd_success) {
    fail("thread pool: could not create mutex");
    return nullptr;
  }

  if (cnd_init(&(pool->wakeup)) != thrd_success) {
    fail("thread pool: could not create condition");
    return nullptr;
  }

  for (unsigned int i = 0; i < threads_capacity; i++) {
    struct thread* thread = pool->threads + i;
    thread->number = i;
    thread->pool = pool;
    if (thrd_create(&(thread->id), thread_main_loop, thread) != thrd_success) {
      fail("thread pool: could not create thread");
      return nullptr;
    }

    if (thrd_detach(pool->threads[i].id) != thrd_success) {
      fail("thread pool: could not detach thread");
      return nullptr;
    }
  }

  return pool;
}

static int0 thread_main_loop (
    void* thread_ptr
)
{
  struct thread* thread = thread_ptr;
  struct thread_pool* pool = thread->pool;
  printl("thread [", f(thread->number), "] started");
  /*
    Lock the mutex `pool->sync`.
    Wait on the condition `pool->wakeup`.
    Pull work from the queue.
    Do work.
    Rinse and repeat.
  */
  int0 result;
  while (pool->active) {
    result = mtx_lock(&(pool->sync));
    if (unlikely(result == thrd_error)) {
      fail("thread pool: mutex error");
      thrd_exit(EXIT_FAILURE);
    }
    printl("thread [", f(thread->number), "] lock");

    result = cnd_wait(&(pool->wakeup), &(pool->sync));
    if (unlikely(result == thrd_error)) {
      fail("thread pool: condition error");
      thrd_exit(EXIT_FAILURE);
    }
    printl("thread [", f(thread->number), "] wait");

    result = mtx_unlock(&(pool->sync));
    if (unlikely(result == thrd_error)) {
      fail("thread pool: mutex error");
      thrd_exit(EXIT_FAILURE);
    }
    printl("thread [", f(thread->number), "] unlock");

    if (!pool->active)
      break;

    printl();
    printl("thread [", f(thread->number), "] working");
    sleep(2*SECONDS);
    printl("thread [", f(thread->number), "] done");
  }

  printl("thread [", f(thread->number), "] exiting");
  thrd_exit(EXIT_SUCCESS);
}
