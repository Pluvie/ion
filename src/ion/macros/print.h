/*
  This macro prints sequentially its arguments over the default print stream.
*/
#define print(...) \
  print_variadic(PRINT_STREAM_DEFAULT, -1 __VA_OPT__(, __VA_ARGS__), nullptr)

/*
  This macro prints sequentially its arguments over the default print stream.
  It also appends a new line at the end.
*/
#define printl(...) \
  print_variadic(PRINT_STREAM_DEFAULT, -1 __VA_OPT__(, __VA_ARGS__), "\n", nullptr)

/*
  This macro prints sequentially its arguments over the given string, up to the
  given length.
*/
#define prints(string, length, ...) \
  print_variadic(string, length __VA_OPT__(, __VA_ARGS__), nullptr)
