
  bool escaped = false;
#ifdef JSON_DISCARD
  char* begin = io->cursor;
#endif

  if (*io->cursor != '"')
    goto error;

  /* Removes the quote " at the beginning.*/
  result->pointer = io->cursor + 1;

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

  if (*io->cursor == '"')
    goto json_parse_string_terminate;

  if (unlikely(io_exhausted(io)))
    goto json_parse_string_error;

  goto read_character;

json_parse_string_terminate:
#ifndef JSON_DISCARD
  /* Removes the quote " at the end.*/
  result->length = (io->cursor) - (result->pointer) - 1;
#endif
  goto parse_success;

json_parse_string_error:
#ifndef JSON_DISCARD
  io_cursor_restore(io, result->pointer);
  *result = (string) { 0 };
#else
  io_cursor_restore(io, begin);
#endif
  goto parse_error;
