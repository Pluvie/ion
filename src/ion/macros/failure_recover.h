/**
 * Recovers a failure. */
#define failure_recover() \
  memzero(&failure, sizeof(struct error))
