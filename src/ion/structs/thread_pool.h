struct thread_pool {
  thrd_t* threads;
  int threads_capacity;
  volatile int num_threads_alive;
  volatile int num_threads_working;
  mtx_t work_sync;
  cnd_t work_available;
  struct {
    void* head;
    void* tail;
  } work_queue;
};
