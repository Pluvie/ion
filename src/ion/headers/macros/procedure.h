/**
 * Automatically begins the function definition for the given *procedure*. */
#define procedure(procedure) \
  struct result__ ## procedure procedure (struct arguments__ ## procedure args)
