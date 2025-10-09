
  while (true) {
    switch (*json_cursor(source)) {
    case ' ':
    case '\n':
    case '\r':
    case '\t':
      json_advance(source, 1);
      continue;
    }

    break;
  }
