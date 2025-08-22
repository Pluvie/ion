/**
 * Sets the global error with the given printf-like *format* string. */
#define fail(format, ...) {                           \
  failure.occurred = true;                            \
  failure.code = errno;                               \
  char message[sizeof(failure.message)] = { 0 };      \
  failure.length = snprintf(                          \
    message, sizeof(message),                         \
    format __VA_OPT__(, __VA_ARGS__));                \
  memcpy(failure.message, message, sizeof(message));  \
}
