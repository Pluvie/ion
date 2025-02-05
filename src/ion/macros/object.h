/**
 * Used to define a code object with an associated schema. */
#define object(var, schema, ...) \
  (struct object) { #var, (void*) &(var), schema __VA_OPT__(, __VA_ARGS__) }
