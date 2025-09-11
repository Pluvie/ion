
  /* Procedure prerequisites on local variables:
   *
   * - `io->cursor` must be a `char*`: it must point to the string to be parsed.
   * - `target` must be a `void*`: it shall be reinterpreted as a `string*` and
   *   shall store the resulting parsed string. */

  bool escaped = false;

#ifndef JSON_DISCARD
  char* begin = io->cursor;
  string* result = (string*) target;
#endif

  if (*io->cursor != '"')
    goto parse_failure;

read_character:
  io_advance(io, 1);

  if (escaped) {
    escaped = false;
    goto read_character;
  }

  if (*io->cursor == 92) {
    escaped = true;
    goto read_character;
  }

  if (*io->cursor == '"') {
    io_advance(io, 1);
    goto parse_success;
  }

  if (unlikely(*io->cursor <= 31)) /* Control characters. */
    goto parse_failure;

  goto read_character;

parse_success:
#ifndef JSON_DISCARD
  /* Removes the quote " at the beginning and end.*/
  result->pointer = begin + 1;
  result->length = (io->cursor) - (result->pointer) - 1;

  if (reflection_validate(rfx, target))
    return;
  else
    goto parse_failure;
#else
  return true;
#endif

parse_failure:
#ifndef JSON_DISCARD
  *result = (string) { 0 };

  if (unlikely(failure.occurred)) {
    /* Keeps the I/O failure message. */

  } else if (io->cursor > begin) {
    fail("invalid string");

  } else {
    io_cursor_restore(io, begin);
    fail("expected a string");
  }

  failure_add_io_info(io);
  failure_add_reflection_info(rfx);
  return;
#else
  return false;
#endif
