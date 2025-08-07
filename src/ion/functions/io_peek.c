slice io_peek (
    struct io* io,
    int amount
)
{
  int cursor = io_cursor_save(io);
  slice peek = io_read(io, amount);
  io_cursor_restore(io, cursor);
  return peek;
}
