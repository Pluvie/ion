/**
 * Helper to wait a fiber. */
#define fiber_wait(var, ...) \
  pthread_join((pthread_t) var.id, NULL);
