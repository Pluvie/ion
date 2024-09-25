/**
 * Automatically defines the result struct for the given *procedure*. */
#define procedure_result(procedure) \
  struct result__ ## procedure
