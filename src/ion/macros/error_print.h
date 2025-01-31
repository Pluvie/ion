/**
 * Prints the error. */
#define error_print() {                         \
  print("Error: %s [%s:%li]",                   \
    error.message, error.file, error.line);     \
}
