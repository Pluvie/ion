
  do {
#ifndef JSON_DISCARD
    number = (10 * number) + (*io->cursor - '0');
#endif
    io_advance(io, 1);
  } while (*io->cursor >= '0' && *io->cursor <= '9');
