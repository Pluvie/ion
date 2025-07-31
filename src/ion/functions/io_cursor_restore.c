static inline void io_cursor_restore (
    struct io* io,
    int position
)
{
  if (io->buffer.enabled) {
    io->buffer.retained = false;
    io->buffer.cursor = position;
    return;
  }

  io->cursor = position;
}
