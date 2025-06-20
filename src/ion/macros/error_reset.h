/**
 * Resets the error. */
#define error_reset() \
  memzero(&error, sizeof(struct failure))
