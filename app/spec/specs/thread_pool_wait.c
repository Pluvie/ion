#include "thread_pool_wait.h"

#if standard(>= C11)
spec( thread_pool_wait ) {
  argument(struct thread_pool* pool);

  precondition("a valid thread pool with queued work");
    #define preconditions \
      pool = thread_pool_create(4); \
      thread_pool_enqueue(pool, example_work, &(int) { 200*MILLISECONDS }); \
      thread_pool_enqueue(pool, example_work, &(int) { 100*MILLISECONDS }); \
      thread_pool_enqueue(pool, example_work, &(int) { 100*MILLISECONDS });

  apply(preconditions);
  must("wait until all threads have completed their work");
    struct chrono wait_time;
    chrono_start(&wait_time);
    thread_pool_wait(pool);
    chrono_stop(&wait_time);
    verify(chrono_elapsed(&wait_time) >= 200*MILLISECONDS);

  success();
    thread_pool_destroy(pool);
}
#endif
