#include "thread_pool_create.h"

spec( thread_pool_create ) {
  argument(unsigned int threads_capacity);

  when("the capacity is not a power of two") {
    printl();
    threads_capacity = 4;
    struct thread_pool* pool = thread_pool_create(threads_capacity);

    //must("return an allocator with capacity equal to the next power of two");
    //  verify(result.capacity == next_pow2(capacity));
    sleep(1*SECOND);
    cnd_signal(&(pool->wakeup));
    sleep(5*SECONDS);
    pool->active = false;
    cnd_broadcast(&(pool->wakeup));
    verify(pool != nullptr);

    success();
      thread_pool_destroy(pool);
  } end();

  //when("the capacity is a power of two") {
  //  capacity = 32;
  //  struct allocator result = thread_pool_create(capacity);

  //  must("return an allocator with the specified capacity");
  //    verify(result.capacity == capacity);

  //  success();
  //} end();
}
