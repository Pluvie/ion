/**
 * Creates an array literal. */
#define array_of(type, ...)                                   \
  (struct array) { .typesize = sizeof(type),                  \
    .data = (type []) __VA_ARGS__,                            \
    .length = sizeof((type []) __VA_ARGS__) / sizeof(type) }
