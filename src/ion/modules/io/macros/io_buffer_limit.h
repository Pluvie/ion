/**
 * Returns the amount of data in the io buffer. */
#define io_buffer_limit(io) \
  ((io)->buffer.allocator.position + (io)->buffer.begin)
