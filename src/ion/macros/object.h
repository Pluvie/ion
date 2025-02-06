/**
 * Used to define a code object with an associated reflection. */
#define object(var, reflection, ...) \
  (struct object) { #var, (void*) &(var), reflection __VA_OPT__(, __VA_ARGS__) }
