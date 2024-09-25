/**
 * Initializes the proc loop for the given *procedure*.
 *
 * This macro is only used in the macro `proc`, to shorten its content. */
#define proc_initializer(procedure, ...) \
  for (struct result__ ## procedure result = procedure(__VA_OPT__((struct arguments__ ## procedure) __VA_ARGS__))
