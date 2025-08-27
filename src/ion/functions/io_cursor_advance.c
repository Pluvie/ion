void io_cursor_advance (
    struct io* io,
    int amount
)
{
  io->cursor += amount;
  io->read.count++;
}
