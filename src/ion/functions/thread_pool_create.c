#include "thread_pool_main_loop.h"
#include "thread_pool_main_loop.c"

struct thread_pool* thread_pool_create (
    unsigned int threads_capacity
)
{
  struct thread_pool* pool = memory_acquire(sizeof(struct thread_pool));
  memory_set(pool, 0, sizeof(*pool));
  pool->active = true;
  pool->threads_capacity = threads_capacity;
  pool->threads = memory_acquire(threads_capacity * sizeof(*(pool->threads)));

  if (mtx_init(&(pool->queue.sync), mtx_plain) != thrd_success) {
    fail("thread pool: could not create queue mutex");
    return nullptr;
  }

  if (mtx_init(&(pool->wakeup.sync), mtx_plain) != thrd_success) {
    fail("thread pool: could not create wakeup mutex");
    return nullptr;
  }

  if (cnd_init(&(pool->queue.cond)) != thrd_success) {
    fail("thread pool: could not create queue condition");
    return nullptr;
  }

  if (cnd_init(&(pool->wakeup.cond)) != thrd_success) {
    fail("thread pool: could not create wakeup condition");
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

  while (pool->num_threads_alive != pool->threads_capacity) { sleep(100*MILLISECONDS); }
  return pool;
}
