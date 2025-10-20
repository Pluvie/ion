void thread_pool_wait (
    struct thread_pool* pool
)
{
  printl("pool wait begin");

  int0 result;
  result = mtx_lock(&(pool->queue.sync));
  if (unlikely(result == thrd_error)) {
    fatal("thread_pool_wait: queue mutex lock error");
    return;
  }

  result = cnd_wait(&(pool->queue.cond), &(pool->queue.sync));
  if (unlikely(result == thrd_error)) {
    fatal("thread_pool_wait: queue cond wait error");
    return;
  }
  printl("pool waiting");

  result = mtx_unlock(&(pool->queue.sync));
  if (unlikely(result == thrd_error)) {
    fatal("thread_pool_wait: queue mutex unlock error");
    return;
  }

  printl("pool wait end");
}
