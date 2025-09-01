
  bool escaped = false;
  char* begin = io->cursor;

  if (*io->cursor != '"')
    goto parse_error;

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
  /* Removes the quote " at the beginning and end.*/
  result->pointer = begin + 1;
  result->length = (io->cursor) - (result->pointer) - 1;
#endif
  goto parse_success;

json_parse_string_error:
#ifndef JSON_DISCARD
  *result = (string) { 0 };
#endif
  io_cursor_restore(io, begin);
  goto parse_error;
