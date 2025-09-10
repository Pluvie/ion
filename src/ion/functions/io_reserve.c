static inline void io_reserve (
    struct io_buffered* io,
    int amount
)
{
  int original_buffer_position = io->buffer.position;

  if (original_buffer_position + amount <= io->buffer.capacity)
    goto read_from_channel;
  else
    goto extend_buffer;

extend_buffer:
  int cursor_offset = io->cursor - io->buffer.data;
  int new_capacity = io->buffer.capacity * 2;
  if (new_capacity < amount)
    new_capacity = amount;

  int padded_capacity = new_capacity + io->buffer.padding_size;
  io->buffer.data = alloc_resize_zero(io->buffer.data, io->buffer.capacity, padded_capacity);
  io->buffer.capacity = new_capacity;
  io->buffer.position = new_capacity;
  io->cursor = io->buffer.data + cursor_offset;

read_from_channel:
  int channel_read_bytes = 0;
  void* storage = io->buffer.data + original_buffer_position;

  switch (io->channel) {
  case IO_PIPE:
    channel_read_bytes = pipe_read(io->pipe, storage, amount);
    if (unlikely(failure.occurred))
      return;

    goto adjust_position;

  default:
    fail("to be implemented");
    return;
  }

adjust_position:
  io->buffer.position -= (amount - channel_read_bytes);
  return;
}
