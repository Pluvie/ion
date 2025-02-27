/**
 * Initializes an io on the specified file stream. */
#define io_file(stream, buffer)                     \
  (struct io) {                                     \
    .file = stream,                                 \
    .length = file_size(stream)                     \
    .channel = IO_CHANNEL_FILE,                     \
    .allocator = buffer,                            \
  }
