/**
 * Macro to check if an I/O has reached the end of input. */
#define io_exhausted(io) \
  *((io)->cursor) == 0
