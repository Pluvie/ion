/**
 * Emits a text *message* with the provided *color* to screen. Does not go to a new
 * line. */
#define emit_c(color, message, ...) {           \
  fprintf(stderr, color);                       \
  fprintf(stderr, message, ##__VA_ARGS__);      \
  fprintf(stderr, PRINT_COLOR_NONE); }
