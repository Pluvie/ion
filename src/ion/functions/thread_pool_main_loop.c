static int0 thread_main_loop (
    void* thread_ptr
)
{
  struct thread* thread = thread_ptr;
  struct thread_pool* pool = thread->pool;
  pool->num_threads_alive++;
  printl("thread [", f(thread->number), "] started");

wait_for_next_job:
  int0 result;
  result = mtx_lock(&(pool->wakeup.sync));
  if (unlikely(result == thrd_error)) {
    fatal("thread_pool_main_loop: wakeup mutex lock error");
    thrd_exit(EXIT_FAILURE);
  }
  printl("thread [", f(thread->number), "] lock");

  result = cnd_wait(&(pool->wakeup.cond), &(pool->wakeup.sync));
  if (unlikely(result == thrd_error)) {
    fatal("thread_pool_main_loop: wakeup cond wait error");
    thrd_exit(EXIT_FAILURE);
  }
  printl("thread [", f(thread->number), "] wait");

  result = mtx_unlock(&(pool->wakeup.sync));
  if (unlikely(result == thrd_error)) {
    fatal("thread_pool_main_loop: wakeup mutex unlock error");
    thrd_exit(EXIT_FAILURE);
  }
  printl("thread [", f(thread->number), "] unlock");

  if (!pool->active)
    goto exit_loop;

  result = mtx_lock(&(pool->queue.sync));
  if (unlikely(result == thrd_error)) {
    fatal("thread_pool_main_loop: queue mutex lock error");
    thrd_exit(EXIT_FAILURE);
  }
  printl("thread [", f(thread->number), "] queue lock");

  struct {
    void (*function)(void*);
    void* argument;
    void* next;
  }* job = pool->queue.first;

  if (likely(job != nullptr))
    pool->queue.first = job->next;

  result = mtx_unlock(&(pool->queue.sync));
  if (unlikely(result == thrd_error)) {
    fatal("thread_pool_main_loop: queue mutex unlock error");
    thrd_exit(EXIT_FAILURE);
  }
  printl("thread [", f(thread->number), "] queue unlock");

  if (unlikely(job == nullptr))
    goto job_done;

  printl();
  pool->num_threads_working++;
  printl("thread [", f(thread->number), "] working");
  job->function(job->argument);
  memory_release(job);
  printl("thread [", f(thread->number), "] done");

job_done:
  pool->num_threads_working--;
  if (pool->num_threads_working == 0) {
    result = cnd_signal(&(pool->queue.cond));
    if (unlikely(result == thrd_error)) {
      fatal("thread_pool_main_loop: queue cond signal error");
      thrd_exit(EXIT_FAILURE);
    }
  }

  if (pool->active)
    goto wait_for_next_job;

exit_loop:
  printl("thread [", f(thread->number), "] exiting");
  pool->num_threads_alive--;
  thrd_exit(EXIT_SUCCESS);
}
