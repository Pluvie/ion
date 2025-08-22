/**
 * Checks if the program has encountered a global failure. */
#define failed(...) \
  (unlikely(failure.occurred __VA_OPTS__(__VA_ARGS__)))
