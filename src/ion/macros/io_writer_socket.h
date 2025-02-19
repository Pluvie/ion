/**
 * Initializes an io writer (with flag #IO_WRITE) on the specified socket descriptor. */
#define io_writer_socket(descriptor)    \
  (struct io) { .socket = descriptor,   \
    .channel = IO_CHANNEL_SOCK,         \
    .mode = IO_MODE_WRITE }
