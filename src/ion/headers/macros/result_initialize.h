/**
 * Automatically initializes the result for the given *procedure*. */
#define result_initialize(procedure) \
  struct result__ ## procedure result = { 0 };
