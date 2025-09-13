/*
  `print` function wrapper to add an explicit new line at the end.
*/
#define println(format, ...) \
  print(format __VA_OPT__(, __VA_ARGS__), f("\n"), nullptr)
