#include "../spec.h"

#if standard(>= C11)
static struct {
  int results[3];
  atomic bool lock_acquired;
} sim;

static void example_work (
    void* sleep_ptr
)
{
  int ms = *(int*) sleep_ptr;
  int number = ms / 1000;
  sleep(ms);
  sim.results[number-1] = number;
}

static int0 example_unlock (
    void* pool_ptr
)
{
  struct thread_pool* pool = pool_ptr;
  mtx_lock(&(pool->queue.sync));
  sim.lock_acquired = true;
  sleep(110*MILLISECONDS);
  mtx_unlock(&(pool->queue.sync));
  thrd_exit(EXIT_SUCCESS);
}
#endif
