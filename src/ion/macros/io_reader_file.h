/**
 * Initializes an io reader (with flag #IO_READ) on the specified file stream. */
#define io_reader_file(stream)        \
  (struct io) { .file = stream,       \
    .channel = IO_CHANNEL_FILE,       \
    .mode = IO_MODE_READ,             \
    .length = file_size(stream) }
