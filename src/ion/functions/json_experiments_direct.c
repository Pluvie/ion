bool json_parse_string_direct (
    struct io_direct* io
)
{
  bool escaped = false;
  io->result.pointer = io->cursor;

  if (*io->cursor != '"')
    goto error;

read_character:
  io_advance(io, 1); // io->cursor += 1;

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

  if (unlikely(io_exhausted(io))) //if (unlikely(*io->cursor == 0))
    goto error;

  goto read_character;

terminate:
  io->result.length = io->cursor - io->result.pointer;
  return;

error:
  *io->result = (string) { 0 };
  io_cursor_restore(io, cursor);
  return;
}



bool json_parse_number_direct (
    struct io_direct* io,
    dec* result
)
{
  io_reserve(io, 128);
  char* number_end;

  *result = strtold(io->cursor, &number_end);
  if (errno == 0) {
    int number_length = (end - data);
    io_advance(io, number_length); // io->cursor += number_length;
    return true;
  }

  return false;
}



bool json_parse_null_direct (
    struct io_direct* io
)
{
  if (io_char_compare(io, "null", sizeof("null")))
    return true;

  return false;
}
