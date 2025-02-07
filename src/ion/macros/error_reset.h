/**
 * Resets the error and its trace. */
#define error_reset() {                           \
  error.occurred = false;                         \
  error.length = 0;                               \
  memzero(error.message, sizeof(error.message));  \
  error.trace_count = 0;                          \
  memzero(error.trace, sizeof(error.trace));      \
}
