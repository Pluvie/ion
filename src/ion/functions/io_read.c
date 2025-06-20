slice io_read (
    struct io* io,
    int amount
)
{
  if (io->buffer.enabled)
    goto read_with_buffer;
  else
    goto read_without_buffer;

read_with_buffer:
  if (unlikely(io->buffer.data == NULL))
    return io_buffer_init(io, amount);

  //io_buffer_compact(io, amount);
  return io_buffer_read(io, amount);

read_without_buffer:
  switch (io->channel) {
  case IO_MEMORY:
    io->storage = io->memory + io->cursor;
    return io_read_channel(io, amount, NULL);

  case IO_FILE:
  case IO_PIPE:
  case IO_SOCKET:
  case IO_STREAM:
    free(io->storage);
    io->storage = malloc(amount);
    return io_read_channel(io, amount, io->storage);

  default:
    return (slice) { 0 };
  }
}
