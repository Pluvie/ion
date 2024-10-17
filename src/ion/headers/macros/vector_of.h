/**
 * Creates an vector literal. */
#define vector_of(type, ...)                                  \
  (struct vector) { .typesize = sizeof(type),                 \
    .data = (type []) __VA_ARGS__,                            \
    .length = sizeof((type []) __VA_ARGS__) / sizeof(type) }
