void thread_pool_destroy (
    struct thread_pool* pool
)
{
  /* Shuts down the queue. */
  pool->active = false;

  for (unsigned int i = 0; i < pool->threads_capacity; i++)
    cnd_broadcast(&(pool->wakeup.cond));

  /* This wait is necessary because the broadcast above may take some time to wake up
    and close properly all threads. */
  sleep(1*SECOND);

  mtx_destroy(&(pool->queue.sync));
  mtx_destroy(&(pool->wakeup.sync));
  cnd_destroy(&(pool->wakeup.cond));

  memory_release(pool->threads);
  memory_release(pool);
}
