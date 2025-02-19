/**
 * Initializes an io writer (with flag #IO_WRITE) on the specified file stream. */
#define io_writer_file(stream)        \
  (struct io) { .file = stream,       \
    .channel = IO_CHANNEL_FILE,       \
    .mode = IO_MODE_WRITE,            \
    .length = file_size(stream) }
