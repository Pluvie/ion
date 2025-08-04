static inline slice io_buffer_init (
    struct io* io,
    int amount
)
{
  if (io->buffer.size <= 0)
    io->buffer.size = 1024;

  int alloc_amount = io->buffer.size;
  if (amount > alloc_amount)
    alloc_amount = io->buffer.size + amount;

  io->buffer.data = malloc(alloc_amount);
  io->buffer.end = alloc_amount;

  slice result = io_read_channel(io, alloc_amount, io->buffer.data);

  if (result.length < amount) {
    io->buffer.end = result.length;
    io->buffer.cursor = result.length;
    return (slice) { io->buffer.data, result.length };

  } else {
    io->buffer.cursor = amount;
    return (slice) { io->buffer.data, amount };
  }
}
