/**
 * Initializes an io writer (with mode #IO_MODE_WRITE) on the specified data with the
 * specified length */
#define io_writer(data_var, length_var)       \
  (struct io) { .memory = (byte*) data_var,   \
    .length = length_var,                     \
    .mode = IO_MODE_WRITE }
