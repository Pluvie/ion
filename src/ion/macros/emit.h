/**
 * Emits a text *message* to screen. Does not go to a new line. */
#define emit(message, ...) \
  fprintf(stderr, message, ##__VA_ARGS__)
