#undef string_print
#define string_print(str, format, ...) \
  snprintf(str.pointer, str.length, format __VA_OPT__(, __VA_ARGS__))
