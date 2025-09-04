
  do {
#ifndef JSON_DISCARD
    accumulator = (10 * accumulator) + (*io->cursor - '0');
#endif
    io_advance(io, 1);
  } while (*io->cursor >= '0' && *io->cursor <= '9');
