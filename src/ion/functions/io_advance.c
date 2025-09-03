static inline void io_advance_direct (
    struct io_direct* io,
    int amount
)
{
  io->cursor += amount;
  /*
  if (likely(io->cursor < io->end)) {
    io->cursor += amount;
    return;
  }

  io->cursor = EMPTY_STRING;
  return;
  */
}



static inline void io_advance_buffered (
    struct io_buffered* io,
    int amount
)
{
/*
  void* address = memory_alloc(io->buffer, amount);
  switch (io->channel) {
  case IO_FILE:
    file_read(io->file, address, amount);
  case IO_PIPE:
    pipe_read(io->file, address, amount);
  case IO_SOCKET:
    socket_read(io->file, address, amount, 0);
  case IO_STREAM:
    stream_read(io->file, address, amount);
  default:
    fail("io: unsupported channel");
  }
  return;
*/
}
