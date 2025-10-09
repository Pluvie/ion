
  if (unlikely(*json_cursor(source) != '"')) {
    fail("expected a string");
    return;
  }

  /* Removes the quote " at the beginning. */
  result.chars = json_cursor(source) + 1;

  do {
    json_advance(source, 1);

    if (*json_cursor(source) == 92) {
      json_advance(source, 2);
      continue;
    }

    if (unlikely(*json_cursor(source) <= 31)) {
      /* ASCII control characters are not allowed in JSON strings. */
      fail("invalid characters in string");
      return;
    }

  } while(*json_cursor(source) != '"');

  json_advance(source, 1);
  /* Removes the quote " at the end. */
  result.length = (json_cursor(source) - result.chars) - 1;
