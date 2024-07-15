/**
 * Initializes an io writer (with flag #IO_WRITE) on the specified socket descriptor. */
#define io_writer_socket(socket)        \
  (struct io) { .descriptor = socket,   \
    .type = IO_TYPE_SOCK,               \
    .flags = IO_WRITE }
