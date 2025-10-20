#include "../spec.h"

static struct {
  int results[3];
  atomic bool lock_acquired;
} sim;

void spec_thread_pool_enqueue__example_work (
    void* sleep_ptr
)
{
  int number = *(int*) sleep_ptr;
  sleep(number*SECONDS);
  sim.results[number-1] = number;
}

int0 spec_thread_pool_enqueue__example_unlock (
    void* pool_ptr
)
{
  struct thread_pool* pool = pool_ptr;
  mtx_lock(&(pool->queue.sync));
  sim.lock_acquired = true;
  sleep(1100*MILLISECONDS);
  mtx_unlock(&(pool->queue.sync));
  thrd_exit(EXIT_SUCCESS);
}
