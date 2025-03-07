/**
 * Initializes an io on the specified memory data. */
#define io_open_memory(memory_var, length_var)      \
  (struct io) {                                     \
    .memory = memory_var,                           \
    .length = length_var,                           \
    .channel = IO_CHANNEL_MEMORY,                   \
  }
