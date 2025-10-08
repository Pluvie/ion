
  while (true) {
    switch (*io_cursor(io)) {
    case ' ':
    case '\n':
    case '\r':
    case '\t':
      io_advance(io, 1);
      continue;
    }

    break;
  }
