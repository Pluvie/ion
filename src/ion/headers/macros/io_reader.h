/**
 * Initializes an io reader (with flag #IO_READ) on the specified data with the
 * specified length. */
#define io_reader(data_var, length_var)       \
  (struct io) { .data = (byte*) data_var,     \
    .length = length_var,                     \
    .flags = IO_READ }
