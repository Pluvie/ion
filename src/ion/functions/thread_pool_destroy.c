void thread_pool_destroy (
    struct thread_pool* pool
)
{
  printl();
  printl();
  printl("pool commencing termination");
  /* Shuts down the pool. */
  pool->active = false;

  for (unsigned int i = 0; i < pool->threads_capacity; i++)
    cnd_broadcast(&(pool->wakeup.cond));

  /* Waits until all threads have finished working. */
  while (pool->num_threads_working != 0) { sleep(100*MILLISECONDS); }
  /* Gives some extra time for thread cleanup after its termination. */
  sleep(1*SECOND);

  mtx_destroy(&(pool->queue.sync));
  mtx_destroy(&(pool->wakeup.sync));
  cnd_destroy(&(pool->queue.cond));
  cnd_destroy(&(pool->wakeup.cond));

  memory_release(pool->threads);
  memory_release(pool);
  printl("pool terminated");
}
