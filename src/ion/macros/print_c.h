/**
 * Prints a text *message* with the provided *color* to screen. Goes to a new line. */
#define print_c(color, message, ...) \
  fprintf(stderr, color message PRINT_COLOR_NONE "\n" __VA_OPT__(, __VA_ARGS__))
