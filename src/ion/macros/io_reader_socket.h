/**
 * Initializes an io reader (with flag #IO_READ) on the specified socket descriptor,
 * and optional flags to add to set the io with. */
#define io_reader_socket(socket, memory, ...)     \
  (struct io) { .descriptor = socket,             \
    .allocator = memory,                          \
    .channel = IO_CHANNEL_SOCK,                   \
    .mode = IO_MODE_READ,                         \
    __VA_OPT__(.flags = __VA_ARGS__) }
