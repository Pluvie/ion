/**
 * Initializes an io reader (with mode #IO_MODE_READ) on the specified data with the
 * specified length. */
#define io_reader(data_var, length_var)       \
  (struct io) { .data = (byte*) data_var,     \
    .length = length_var,                     \
    .channel = IO_CHANNEL_MEM,                \
    .mode = IO_MODE_READ }
