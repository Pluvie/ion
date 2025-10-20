void thread_pool_destroy (
    struct thread_pool* pool
)
{
  mtx_destroy(&(pool->work_sync));
  cnd_destroy(&(pool->work_available));
  free(pool->threads);
  free(pool);
}
