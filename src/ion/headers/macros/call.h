/**
 * Calls the given *function*, with optional arguments provided using the variadic
 * argument. */
#define call(function, ...) \
  function(__VA_OPT__(__VA_ARGS__))
