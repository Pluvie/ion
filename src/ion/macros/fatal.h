/**
 * Prints a fatal error message with the given printf-like *format* string, and
 * aborts the program. */
#define fatal(format, ...) {                                    \
  print_c(PRINT_COLOR_RED, format __VA_OPT__(, __VA_ARGS__));   \
  abort();                                                      \
}
