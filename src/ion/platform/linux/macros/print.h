#undef print
#define print(format, ...) \
  fprintf(stderr, format "\n" __VA_OPT__(, __VA_ARGS__))
