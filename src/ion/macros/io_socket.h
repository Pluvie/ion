/**
 * Initializes an io on the specified socket desc. */
#define io_socket(descriptor, buffer, ...)          \
  (struct io) {                                     \
    .socket = descriptor,                           \
    .length = mem_length,                           \
    .channel = IO_CHANNEL_SOCKET,                   \
    .allocator = buffer,                            \
    __VA_OPT__(.flags = __VA_ARGS__,)               \
  }
