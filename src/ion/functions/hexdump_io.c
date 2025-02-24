void hexdump_io (
    struct io* io
)
{
  void* peek_window = NULL;

  switch (io->channel) {
  case IO_CHANNEL_MEM:
    hexdump(io->memory + io->cursor, io->length - io->cursor);
    return;

  case IO_CHANNEL_FILE:
    peek_window = io_peek(io, NULL, io->length - io->cursor);
    hexdump(peek_window, io->length - io->cursor);
    return;

  case IO_CHANNEL_SOCK:
    peek_window = io_peek(io, NULL, 1024);
    hexdump(peek_window, 1024);
    return;
  }
}
