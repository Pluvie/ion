#undef stream_print
#define stream_print(stream, format, ...) \
  fprintf(stderr, format __VA_OPT__(, __VA_ARGS__))
