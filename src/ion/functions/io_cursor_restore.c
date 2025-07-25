static inline void io_cursor_restore (
    struct io* io,
    int position
)
{
  if (io->buffer.enabled)
    io->buffer.cursor = position;
  else
    io->cursor = position;
}
