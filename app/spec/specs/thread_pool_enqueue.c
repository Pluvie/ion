#include "thread_pool_enqueue.h"

#if standard(>= C11)
spec( thread_pool_enqueue ) {
  argument(struct thread_pool* pool);
  argument(void (*function)(void*));
  argument(void* argument);

  precondition("a valid thread pool");
    #define preconditions \
      pool = memory_acquire(sizeof(*pool)); \
      memory_set(pool, 0, sizeof(*pool)); \
      mtx_init(&(pool->queue.sync), mtx_plain); \
      mtx_init(&(pool->wakeup.sync), mtx_plain); \
      cnd_init(&(pool->queue.cond)); \
      cnd_init(&(pool->wakeup.cond));

  when("the pool queue mutex is unlocked") {
    apply(preconditions);
    mtx_unlock(&(pool->queue.sync));

    when("the pool queue is empty") {
      pool->queue.first = nullptr;
      pool->queue.last = nullptr;
      function = example_work;
      argument = &(int) { 100*MILLISECONDS };
      thread_pool_enqueue(pool, function, argument);

      must("successfully enqueue the job in the pool");
        verify(pool->queue.first != nullptr);
        verify(pool->queue.last != nullptr);
        struct { void* function; int* argument; void* next; }* job = pool->queue.first;
        verify(job->function == example_work);
        verify(job->next == nullptr);
        verify(*(job->argument) == 100*MILLISECONDS);

      success();
        /* The next test is consequential so we destroy the pool there. */
    } end();

    when("the pool queue is not empty") {
      verify(pool->queue.first != nullptr);
      verify(pool->queue.last != nullptr);
      function = example_work;
      argument = &(int) { 200*MILLISECONDS };
      thread_pool_enqueue(pool, function, argument);

      must("successfully enqueue the job in the pool");
        verify(pool->queue.first != nullptr);
        verify(pool->queue.last != nullptr);

      must("correctly queue the job after the first");
        struct { void* function; int* argument; void* next; }* job = pool->queue.last;
        struct { void* function; int* argument; void* next; }* first = pool->queue.first;
        verify(first->next == job);
        verify(job->function == example_work);
        verify(job->next == nullptr);
        verify(*(job->argument) == 200*MILLISECONDS);

      success();
        thread_pool_destroy(pool);
        memory_release(job);
        memory_release(first);
    } end();
  } end();

  when("the pool queue mutex is locked") {
    #define locked_queue_mutex_condition \
      thrd_t locking_thread; thrd_create(&locking_thread, example_unlock, pool); \
      while (sim.lock_acquired == false) \
        sleep(10*MILLISECONDS); /* Lets the locking thread acquire the mutex lock. */

    apply(preconditions);
    apply(locked_queue_mutex_condition);

    struct chrono wait_time;
    chrono_start(&wait_time);
    function = example_work;
    argument = &(int) { 100*MILLISECONDS };
    thread_pool_enqueue(pool, function, argument);
    chrono_stop(&wait_time);

    must("wait the mutex to unlock and then successfully enqueue the job in the pool");
      verify(chrono_elapsed(&wait_time) >= 100*MILLISECOND);
      verify(pool->queue.first != nullptr);
      verify(pool->queue.last != nullptr);
      struct { void* function; int* argument; void* next; }* job = pool->queue.first;
      verify(job->function == example_work);
      verify(job->next == nullptr);
      verify(*(job->argument) == 100*MILLISECONDS);

    success();
      thrd_join(locking_thread, nullptr);
      thread_pool_destroy(pool);
      memory_release(job);
  } end();
}
#endif
