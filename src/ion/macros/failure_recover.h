/**
 * Recovers a failure. */
#define failure_recover() \
  zero_out(&failure, sizeof(struct error))
