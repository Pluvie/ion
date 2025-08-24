void io_peek (
    struct io* io,
    int amount
)
{
  int cursor = io_cursor_save(io);
  io_read(io, amount);
  io_cursor_restore(io, cursor);
}
