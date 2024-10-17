/**
 * Used to reference another previously defined protocol schema to handle a struct. */
#define schema(schema_name)             \
  .child = (schema_name)->child,        \
  .bounds = {                           \
    (schema_name)->bounds[0],           \
    (schema_name)->bounds[1]            \
  }
