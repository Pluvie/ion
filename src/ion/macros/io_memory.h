/**
 * Initializes an io on the specified memory data. */
#define io_memory(data, mem_length)                 \
  (struct io) {                                     \
    .memory = data,                                 \
    .length = mem_length,                           \
    .channel = IO_CHANNEL_MEMORY,                   \
  }
