/**
 * Used to reference another previously defined reflection to handle a struct. */
#define reflect(reflection)               \
  .child = (reflection)->child,           \
  .validator = (reflection)->validator,   \
  .bounds = {                             \
    (reflection)->bounds[0],              \
    (reflection)->bounds[1]               \
  }
