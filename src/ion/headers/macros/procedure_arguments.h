/**
 * Automatically defines the arguments struct for the given *procedure*. */
#define procedure_arguments(procedure) \
  struct arguments__ ## procedure
