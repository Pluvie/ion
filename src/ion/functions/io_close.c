void io_close (
    struct io* io
)
{
  if (io->buffer.enabled)
    return free(io->buffer.data.pointer);

  switch (io->channel) {
  case IO_MEMORY:
    return;

  case IO_FILE:
  case IO_PIPE:
  case IO_SOCKET:
  case IO_STREAM:
    return free(io->result.pointer);
  }
}
