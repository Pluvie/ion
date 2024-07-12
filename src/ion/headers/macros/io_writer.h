/**
 * Initializes an io writer (with flag #IO_WRITER) on the specified data with the
 * specified length. Optionally gives an allocator to dynamically resize the data. */
#define io_writer(data_var, length_var, ...)  \
  (struct io) { .data = (byte*) data_var,     \
    .length = length_var,                     \
    .flags = IO_WRITE,                        \
    __VA_OPT__(, .allocator = __VA_ARGS__) }
