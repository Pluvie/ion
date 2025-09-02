
  char* number_end;

#ifndef JSON_DISCARD
  *result = strtold(io->cursor, &number_end);
#else
  strtold(io->cursor, &number_end);
#endif

  int number_length = (number_end - io->cursor);
  if (errno == 0 && number_length > 0) {
    io_advance(io, number_length);
#ifndef JSON_DISCARD
    /* To be implemented. */
#else
    return true;
#endif
  }

#ifndef JSON_DISCARD
  /* To be implemented. */
#else
  return false;
#endif
