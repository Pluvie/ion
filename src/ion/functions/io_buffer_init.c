void io_buffer_init (
    struct io* io,
    int amount
)
{
  if (io->buffer.size <= 0)
    io->buffer.size = 1024;

  int alloc_amount = io->buffer.size;
  if (amount > alloc_amount)
    alloc_amount = io->buffer.size + amount;

  io->buffer.data.pointer = alloc_zero(alloc_amount);
  io_channel_read(io, alloc_amount, io->buffer.data.pointer);
  if (unlikely(failure.occurred))
    return;

  int channel_available_data = io->result.length;
  io->buffer.data.length = channel_available_data;

  if (channel_available_data < amount) {
    io->buffer.cursor = channel_available_data;
    io->result = (string) { io->buffer.data.pointer, channel_available_data };
  } else {
    io->buffer.cursor = amount;
    io->result = (string) { io->buffer.data.pointer, amount };
  }
}
