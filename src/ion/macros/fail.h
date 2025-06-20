/**
 * Sets a failure with the given printf-like *format* string. */
#define fail(format, ...) {                         \
  error.occurred = true;                            \
  error.code = errno;                               \
  char message[sizeof(error.message)] = { 0 };      \
  error.length = snprintf(                          \
    message, sizeof(message),                       \
    format __VA_OPT__(, __VA_ARGS__));              \
  memcpy(error.message, message, sizeof(message));  \
}
