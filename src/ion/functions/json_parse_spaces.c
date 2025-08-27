int json_parse_spaces (
    struct io* io
)
{
  int cursor = io_cursor_save(io);
  int length = 0;
  char character;

read_character:
  io_read(io, sizeof(char));
  if (unlikely(failure.occurred))
    goto error;

  if (io->result.length == 0)
    goto terminate;

  character = string_char_at(io->result, 0);
  if (isspace(character)) {
    length++;
    goto read_character;
  }

terminate:
  io_cursor_restore(io, cursor);
  io_read(io, length);
  return length;

error:
  io_cursor_restore(io, cursor);
  return -1;
}
