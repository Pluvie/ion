/*
  Prints a formatted message on the stderr stream and adds a new line at the end.
*/
#define print(...) \
  print_formatted(stderr, __VA_OPT__(__VA_ARGS__,) "\n", nullptr)
