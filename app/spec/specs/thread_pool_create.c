#include "thread_pool_create.h"

spec( thread_pool_create ) {
  argument(unsigned int threads_capacity);

  when("the capacity is not a power of two") {
    printl();
    threads_capacity = 4;
    struct thread_pool* pool = thread_pool_create(threads_capacity);

    //must("return an allocator with capacity equal to the next power of two");
    //  verify(result.capacity == next_pow2(capacity));
    verify(pool != nullptr);

    thread_pool_enqueue(pool, example_work, &(int) { 3 });
    thread_pool_enqueue(pool, example_work, &(int) { 2 });
    thread_pool_enqueue(pool, example_work, &(int) { 1 });

    //sleep(7*SECONDS);
    thread_pool_wait(pool);

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
