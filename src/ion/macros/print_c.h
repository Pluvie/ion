/**
 * Prints a text *message* with the provided *color* to screen. Goes to a new line. */
#define print_c(color, message, ...) {          \
  fprintf(stderr, color);                       \
  fprintf(stderr, message "\n", ##__VA_ARGS__); \
  fprintf(stderr, PRINT_COLOR_NONE); }
