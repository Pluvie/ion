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
    if (io->storage != NULL)
      return io_read_channel(io, amount, io->storage);

    fatal("%li, not enough memory", amount);

  default:
    return (slice) { 0 };
  }
}
