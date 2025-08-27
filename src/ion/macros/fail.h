/**
 * Sets the global error with the given printf-like *format* string. */
#define fail(format, ...) {                                     \
  failure.occurred = true;                                      \
                                                                \
  char _tmp[sizeof(failure._message_data)] = { 0 };             \
  string tmp = { _tmp, sizeof(_tmp) };                          \
  string_print(tmp, format __VA_OPT__(, __VA_ARGS__));          \
                                                                \
  failure.message.pointer = failure._message_data;              \
  byte_copy(                                                    \
    failure.message.pointer,                                    \
    tmp.pointer,                                                \
    tmp.length);                                                \
}
