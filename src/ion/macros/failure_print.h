/**
 * Prints the failure. */
#define failure_print() \
  print_c(PRINT_COLOR_RED, "\nError: %.*s", sp(failure.message))
