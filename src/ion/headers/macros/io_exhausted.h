/**
 * Checks if the io cursor has reached the io length. */
#define io_exhausted(io) \
  ((io)->type != IO_TYPE_SOCK ? ((io)->cursor == (io)->length) : false)
