struct thread_pool {
  struct thread* threads;
  unsigned int threads_capacity;
  volatile atomic bool active;
  volatile atomic unsigned int num_threads_alive;
  volatile atomic unsigned int num_threads_working;
  struct {
    mtx_t sync;
    cnd_t cond;
  } wakeup;
  struct {
    mtx_t sync;
    void* first;
    void* last;
  } queue;
};
