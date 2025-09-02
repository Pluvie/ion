
  do {
    number = (10 * number) + (((unsigned char) *io->cursor) - '0');
    io_advance(io, 1);
  } while (*io->cursor >= '0' && *io->cursor <= '9');
