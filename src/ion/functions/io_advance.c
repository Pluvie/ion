static inline void io_advance_direct (
    struct io_direct* io,
    int amount
)
{
  io->cursor += amount;
}



static inline void io_advance_buffered (
    struct io_buffered* io,
    int amount
)
{
  int cursor_position = io->cursor - io->buffer.data;
  int available_amount = io->buffer.position - cursor_position;

  if (amount > available_amount)
    io_reserve(io, io->buffer.window_size);

  io->cursor += amount;
  return;
}
