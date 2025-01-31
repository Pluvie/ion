/**
 * Resets the error. */
#define error_reset() {                           \
  error.occurred = false;                         \
  error.length = 0;                               \
  memzero(error.message, sizeof(error.message));  \
}
