/**
 * Creates an array literal. */
#define arrayof(type, ...)                                    \
  { .typesize = sizeof(type),                                 \
    .data = (type []) __VA_ARGS__,                            \
    .length = sizeof((type []) __VA_ARGS__) / sizeof(type) }
