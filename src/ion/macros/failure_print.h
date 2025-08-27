/**
 * Prints the failure. */
#define failure_print() \
  print_c(PRINT_COLOR_RED, "Error: %.*s", sp(failure.message))
