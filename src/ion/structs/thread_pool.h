struct thread_pool {
  bool active;
  struct thread* threads;
  unsigned int threads_capacity;
  volatile unsigned int num_threads_alive;
  volatile unsigned int num_threads_working;
  mtx_t sync;
  cnd_t wakeup;
  struct {
    void* head;
    void* tail;
  } work_queue;
};
