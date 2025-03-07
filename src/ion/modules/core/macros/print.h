/**
 * Prints a text *message* to screen. Goes to a new line. */
#define print(message, ...)                     \
  fprintf(stderr, message "\n", ##__VA_ARGS__)
