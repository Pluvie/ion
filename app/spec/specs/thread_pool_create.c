#include "thread_pool_create.h"

spec( thread_pool_create ) {
  argument(unsigned int threads_capacity);

  threads_capacity = 4;
  struct thread_pool* pool = thread_pool_create(threads_capacity);

  must("successfully create the thread pool");
    verify(pool != nullptr);
    verify(pool->threads_capacity == threads_capacity);

  success();
    thread_pool_destroy(pool);
}
