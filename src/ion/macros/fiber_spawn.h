/**
 * Helper to spawn a fiber. */
#define fiber_spawn(var, ...) \
  pthread_create((pthread_t*) &(var.id), NULL __VA_OPT__(| __VA_ARGS__), var.function, (void*) &var);
