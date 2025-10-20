/*
  This static function does the main thread loop which keeps a thread on hold on a
  condition variable (`pool->wakeup.cond`) until there's work to do in the pool queue.

  The logic of the loop is:
    - Lock the mutex `pool->wakeup.sync`.
    - Wait on the condition `pool->wakeup.cond`.
    - Unlock the mutex `pool->wakeup.sync`.
    - Lock the mutex `pool->queue.sync`.
    - Pull work from the queue.
    - Unlock the mutex `pool->queue.sync`.
    - Do the assigned work.
    - Rinse and repeat.

  The `pool->wakeup.sync` mutex is necessary in order to ensure that only one thread
  at a time is waiting on the condition `pool->wakeup.cond` to avoid data races.

  After the thread that is waiting on the condition is signaled -- look at the function
  `thread_pool_enqueue`, it immediately and atomically pulls the first job from the
  queue, by syncing on the `pool->queue.sync` mutex.

  Then it executes the function pointer of the job, using the provided argument, and
  restarts the loop again.

  The loop ends when the `pool->active` variable is found false.
*/
static int0 thread_main_loop (
    void* thread_ptr
);
