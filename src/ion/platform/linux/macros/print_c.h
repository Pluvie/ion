#undef print_c
#define print_c(color, format, ...) \
  fprintf(stderr, color format PRINT_COLOR_NONE "\n" __VA_OPT__(, __VA_ARGS__))
