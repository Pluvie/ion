int json_parse_string (
    struct io* io
)
{
  int cursor = io_cursor_save(io);
  int length = 0;
  bool escaped = false;
  char character;

  io_read(io, sizeof(char));
  if (unlikely(failure.occurred))
    goto error;

  if (io->result.length == 0)
    goto error;

  character = string_char_at(io->result, 0);
  if (character != '"')
    goto error;

  length++;

read_character:
  io_read(io, sizeof(char));
  if (unlikely(failure.occurred))
    goto error;

  if (io->result.length == 0)
    goto error;

  if (escaped) {
    escaped = false;
    length++;
    goto read_character;
  }

  character = string_char_at(io->result, 0);
  if (character == 92) {
    escaped = true;
    length++;
    goto read_character;
  }

  if (character == '"') {
    length++;
    goto terminate;
  }

  length++;
  goto read_character;

terminate:
  io_cursor_restore(io, cursor);
  io_read(io, length);
  return length;

error:
  io_cursor_restore(io, cursor);
  return -1;

  #undef character
}
