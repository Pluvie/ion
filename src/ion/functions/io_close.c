void io_close (
    struct io* io
)
{
  if (io->buffer.enabled)
    return alloc_release(io->buffer.data.pointer);

  if (io->channel != IO_MEMORY)
    return alloc_release(io->result.pointer);
}
