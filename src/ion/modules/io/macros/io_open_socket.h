/**
 * Initializes an io on the specified socket descriptor. */
#define io_open_socket(socket_var, ...)                     \
  (struct io) {                                             \
    .socket = socket_var,                                   \
    .channel = IO_CHANNEL_SOCKET,                           \
    .buffer = {                                             \
      .begin = 0,                                           \
      .size = IO_BUFFER_DEFAULT_SIZE,                       \
      .allocator = buffer_init(4*IO_BUFFER_DEFAULT_SIZE),   \
    },                                                      \
    __VA_OPT__(.flags = __VA_ARGS__,)                       \
  }
