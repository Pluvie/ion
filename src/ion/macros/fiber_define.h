/**
 * Helper to define a fiber. */
#define fiber_define(name, ...) \
  struct fiber(name) { \
    int id; \
    void* (*function)(void*); \
    struct __VA_ARGS__ args; \
  };
