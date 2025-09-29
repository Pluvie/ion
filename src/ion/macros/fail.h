/*
  Fails on the global failure variable.
*/
#define fail(...) \
  print_failure(false __VA_OPT__(,) __VA_ARGS__, nullptr)
