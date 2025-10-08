
  if (unlikely(*io_cursor(io) != '"')) {
    fail("expected a string");
    return;
  }

  /* Removes the quote " at the beginning. */
  result.chars = io_cursor(io) + 1;

  do {
    io_advance(io, 1);

    if (*io_cursor(io) == 92) {
      io_advance(io, 2);
      continue;
    }

    if (unlikely(*io_cursor(io) <= 31)) {
      /* ASCII control characters are not allowed in JSON strings. */
      fail("invalid characters in string");
      return;
    }

  } while(*io_cursor(io) != '"');

  io_advance(io, 1);
  /* Removes the quote " at the end. */
  result.length = (io_cursor(io) - result.chars) - 1;
