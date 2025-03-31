/**
 * Initializes an io on the specified file stream. */
#define io_open_file(file_var, ...)                         \
  (struct io) {                                             \
    .file = file_var,                                       \
    .length = (__VA_OPT__(1+)0) ?                           \
      __VA_OPT__((__VA_ARGS__)+)0 :                         \
      file_size(file_var),                                  \
    .channel = IO_CHANNEL_FILE,                             \
    .buffer = {                                             \
      .begin = 0,                                           \
      .size = IO_BUFFER_DEFAULT_SIZE,                       \
      .allocator = buffer_init(4*IO_BUFFER_DEFAULT_SIZE),   \
    },                                                      \
  }
