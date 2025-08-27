/**
 * Prints a text *message* with the provided *color* to screen. */
#define print_c(color, message, ...) \
  print(color message PRINT_COLOR_NONE __VA_OPT__(, __VA_ARGS__)
