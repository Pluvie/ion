/**
 * Creates an array literal. */
#define array_of(t, ...) \
  (array(t)) { .elements = (t []) __VA_ARGS__, .length = sizeof((t []) __VA_ARGS__) / sizeof(t) }
