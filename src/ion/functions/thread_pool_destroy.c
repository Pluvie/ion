void thread_pool_destroy (
    struct thread_pool* pool
)
{
  for (unsigned int i = 0; i < pool->threads_capacity; i++)
    cnd_broadcast(&(pool->wakeup));

  sleep(1*SECOND);
  mtx_destroy(&(pool->sync));
  cnd_destroy(&(pool->wakeup));
  free(pool->threads);
  free(pool);
}
