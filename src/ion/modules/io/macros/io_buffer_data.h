/**
 * Returns the data from the io buffer. */
#define io_buffer_data(io)  \
  buffer_data(&((io)->buffer.allocator), (io)->cursor - (io)->buffer.begin);
