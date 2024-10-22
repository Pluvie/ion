/**
 * Creates an vector literal on the stack. */
#define vector_static(type, len)                \
  (struct vector) { .typesize = sizeof(type),   \
    .data = alloca(sizeof(type) * len),         \
    .length = len }
