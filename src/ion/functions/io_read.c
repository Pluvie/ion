void io_read (
    struct io* io,
    int amount
)
{
  if (io->buffer.enabled)
    return io_buffer_read(io, amount);

  if (io->channel == MEMORY)
    return io_channel_read(io, amount, NULL);

  free(io->data.pointer);
  io->data.pointer = alloc_zero(amount);
  return io_channel_read(io, amount, io->data.pointer);
}
