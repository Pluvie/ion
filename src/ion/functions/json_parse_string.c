{
  bool escaped = false;
#ifndef JSON_DISCARD
  result->pointer = io->cursor;
#else
  char* begin = io->cursor;
#endif

  if (*io->cursor != '"')
    goto error;

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
    goto terminate;

  if (unlikely(io_exhausted(io)))
    goto error;

  goto read_character;

terminate:
#ifndef JSON_DISCARD
  result->length = io->cursor - (char*) result->pointer;
#endif
  return true;

error:
#ifndef JSON_DISCARD
  io_cursor_restore(io, result->pointer);
  *result = (string) { 0 };
#else
  io_cursor_restore(io, begin);
#endif
  return false;
}
