static inline int io_cursor_save (
    struct io* io
)
{
  if (io->buffer.enabled)
    return io->buffer.cursor;
  else
    return io->cursor;
}
