static inline void io_buffer_init (
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

  if (io->result.length < alloc_amount)
    io->buffer.data.length = io->result.length;
  else
    io->buffer.data.length = alloc_amount;

  if (io->result.length < amount)
    io->buffer.cursor = io->result.length;
  else
    io->buffer.cursor = amount;
}
