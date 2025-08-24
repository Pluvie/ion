static inline void io_channel_read (
    struct io* io,
    int amount,
    void* address
)
{
  switch (io->channel) {
  case IO_MEMORY:
    if (unlikely(io->cursor + amount > io->length))
      amount = io->length - io->cursor;

    if (unlikely(amount <= 0)) {
      io->result.pointer = NULL;
      io->result.length = 0;
      return;
    }

    io->result.pointer = io->memory + io->cursor;
    io->result.length = amount;
    io_cursor_advance(io, amount);
    return;

  case IO_FILE:
    io->result.length = file_read(io->file, address, amount);
    break;

  case IO_PIPE:
    io->result.length = pipe_read(io->pipe, address, amount);
    break;

  case IO_SOCKET:
    io->result.length = socket_read(io->socket, address, amount, io->read.flags);
    break;

  case IO_STREAM:
    io->result.length = amount;
    stream_read(io->stream, address, amount);
    break;

  default:
    fail("io: invalid channel");
    return;
  }

  if (unlikely(failure.occurred))
    return;

  io->result.pointer = address;
  io_cursor_advance(io, io->result.length);
  return;
}
