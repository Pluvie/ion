void thread_pool_enqueue (
    struct thread_pool* pool,
    void (*function)(void*),
    void* argument
)
{
  int0 result;

  result = mtx_lock(&(pool->queue.sync));
  if (unlikely(result == thrd_error)) {
    fatal("thread_pool_enqueue: queue mutex lock error");
    return;
  }

  struct {
    void (*function)(void*);
    void* argument;
    void* next;
  }* job;

  struct {
    void (*function)(void*);
    void* argument;
    void* next;
  }* last = pool->queue.last;

  job = memory_acquire(sizeof(*job));
  job->function = function;
  job->argument = argument;
  job->next = nullptr;

  if (last != nullptr) {
    last->next = job;
    pool->queue.last = job;

  } else if (pool->queue.first == nullptr) {
    pool->queue.first = job;
    pool->queue.last = job;

  } else {
    fatal("thread_pool_enqueue: corrupted queue");
    return;
  }

  result = mtx_unlock(&(pool->queue.sync));
  if (unlikely(result == thrd_error)) {
    fatal("thread_pool_enqueue: queue mutex unlock error");
    return;
  }

  result = cnd_signal(&(pool->wakeup.cond));
  if (unlikely(result == thrd_error)) {
    fatal("thread_pool_enqueue: wakeup cnd_signal error");
    return;
  }
}
