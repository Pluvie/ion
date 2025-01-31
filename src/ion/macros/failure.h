/**
 * Set a failure with the given printf-like *format* string. */
#define failure(f, format, ...) { \
  (f)->occurred = true;           \
  (f)->length = snprintf(         \
    (f)->message,                 \
    sizeof((f)->message),         \
    format,                       \
    ##__VA_ARGS__);               \
}
