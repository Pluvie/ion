/**
 * Prints the error. */
#define error_print() \
  print_c(PRINT_COLOR_RED, "Error: %s", error.message)
