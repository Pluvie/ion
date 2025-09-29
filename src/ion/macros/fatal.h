/*
  Fails on the global failure variable and aborts the program.
*/
#define fatal(...) \
  print_failure(true __VA_OPT__(,) __VA_ARGS__, nullptr)
