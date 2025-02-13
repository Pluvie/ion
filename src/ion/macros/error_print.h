/**
 * Prints the error. */
#define error_print() {                                   \
  print_c(PRINT_COLOR_RED, "Error: %s", error.message);   \
  for (i32 i = error.trace_count - 1; i >= 0; i--)        \
    print_c(PRINT_COLOR_RED, "[%s:%li]",                  \
      error.trace[i].file, error.trace[i].line);          \
}
