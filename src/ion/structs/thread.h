struct thread {
  thrd_t id;
  struct thread_pool* pool;
  unsigned int number;
};
