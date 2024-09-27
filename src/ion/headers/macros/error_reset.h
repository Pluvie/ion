/**
 * Resets the error. */
#define error_reset() {                         \
  error.occurred = false;                       \
  error.length = 0;                             \
  bzero(error.message, sizeof(error.message));  \
}
