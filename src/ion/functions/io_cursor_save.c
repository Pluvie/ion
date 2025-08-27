int io_cursor_save (
    struct io* io
)
{
  if (io->buffer.enabled) {
    io->buffer.retained = true;
    return io->buffer.cursor;
  }

  return io->cursor;
}
