/**
 * Helper to initialize a fiber by its name. */
#define fiber_init(name, ...) \
  (struct fiber(name)) { .function = fiber(name), .args = __VA_ARGS__ };
