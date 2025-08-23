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
      io->data.pointer = NULL;
      io->data.length = 0;
      return;
    }

    io->data.pointer = io->memory + io->cursor;
    io->data.length = amount;
    io_cursor_advance(io, amount);
    return;

  case IO_FILE:
    io->data.length = file_read(io->file, address, amount);
    break;

  case IO_PIPE:
    io->data.length = pipe_read(io->pipe, address, amount);
    break;

  case IO_SOCKET:
    io->data.length = socket_read(io->socket, address, amount, io->read.flags);
    break;

  case IO_STREAM:
    io->data.length = stream_read(io->socket, address, amount);
    break;

  default:
    fail("io: invalid channel");
    return;
  }

  if (unlikely(failure.occurred))
    return;

  io->data.pointer = address;
  io_cursor_advance(io, io->data.length);
  return;
}
