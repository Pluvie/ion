/**
 * Checks if the io cursor has reached the io length. */
#define io_exhausted(io) \
  ((io)->cursor == (io)->length)
