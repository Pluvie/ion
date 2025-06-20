/**
 * Emits a text *message* with the provided *color* to screen. Does not go to a new
 * line. */
#define emit_c(color, message, ...) \
  fprintf(stderr, color message PRINT_COLOR_NONE __VA_OPT__(, __VA_ARGS__))
