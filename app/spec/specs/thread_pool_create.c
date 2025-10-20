#include "thread_pool_create.h"

spec( thread_pool_create ) {
  argument(unsigned int threads_capacity);

  when("the capacity is greater than 0") {
    threads_capacity = 4;
    struct thread_pool* pool = thread_pool_create(threads_capacity);
    thread_pool_enqueue(pool, example_work, &(int) { 3 });
    thread_pool_enqueue(pool, example_work, &(int) { 2 });
    thread_pool_enqueue(pool, example_work, &(int) { 1 });
    thread_pool_wait(pool);

    must("successfully create the thread pool");
      verify(pool != nullptr);
      verify(pool->threads_capacity == threads_capacity);

    must("correctly schedule the threads in order to complete the queued jobs");
      verify(sim.results[0] == 1);
      verify(sim.results[1] == 2);
      verify(sim.results[2] == 3);

    success();
      thread_pool_destroy(pool);
  } end();
}
