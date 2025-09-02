
  io_reserve(io, 128);
  char* number_end;

#ifndef JSON_DISCARD
  *result = strtold(io->cursor, &number_end);
#else
  strtold(io->cursor, &number_end);
#endif

  if (errno == 0) {
    int number_length = (number_end - io->cursor);
    io_advance(io, number_length);
    goto parse_success;
  }

  goto parse_failure;

parse_success:
#ifndef JSON_DISCARD
#else
  return true;
#endif

parse_failure:
#ifndef JSON_DISCARD
#else
  return false;
#endif
