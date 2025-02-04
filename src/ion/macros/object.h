/**
 * Used to define a code object with an associated schema. */
#define object(var, schema, allocator) \
  (struct object) { #var, (void*) &(var), schema, allocator }
