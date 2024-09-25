/**
 * Sets a failure with the given printf-like *format* string. */
#define fail(format, ...) {             \
  error.occurred = true;                \
  error.length = snprintf(              \
    error.message,                      \
    sizeof(error.message),              \
    format __VA_OPT__(, __VA_ARGS__));  \
}
