/**
 * Sets the error with the info coming from the given io, and adding information
 * about the position where it occurred. */
#define io_failure(io, ...) {                   \
  fail(__VA_ARGS__);                            \
  io_failure_position(io, __FILE__, __LINE__);  \
}
