/**
 * Initializes an io reader (with flag #IO_READ) on the specified socket descriptor. */
#define io_reader_socket(socket, memory)  \
  (struct io) { .descriptor = socket,     \
    .allocator = memory,                  \
    .type = IO_TYPE_SOCK,                 \
    .flags = IO_READ }
