/**
 * Used to reference another previously defined reflection to handle a struct. */
#define reflect(reflection)               \
  .size = (reflection)->size,             \
  .fields = (reflection)->fields,         \
  .validator = (reflection)->validator,   \
  .size_limits = {                        \
    (reflection)->size_limits.min,        \
    (reflection)->size_limits.max         \
  }
