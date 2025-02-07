/**
 * Initializes an io writer (with mode #IO_MODE_WRITE) on the specified data with the
 * specified length. Optionally gives an allocator to dynamically resize the data. */
#define io_writer(data_var, length_var, ...)  \
  (struct io) { .data = (byte*) data_var,     \
    .length = length_var,                     \
    .mode = IO_MODE_WRITE,                    \
    __VA_OPT__(.allocator = __VA_ARGS__) }
