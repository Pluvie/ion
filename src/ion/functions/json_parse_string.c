static inline int json_parse_string (
    struct io* io
)
{
  int cursor = io_cursor_save(io);
  int length = 0;
  bool escaped = false;
  slice result;
  #define character ((char*) result.data)[0]

  result = io_read(io, sizeof(char));
  if (error.occurred)
    goto error;

  if (result.length == 0)
    goto error;

  if (character != '"')
    goto error;

  length++;

read_character:
  result = io_read(io, sizeof(char));
  if (error.occurred)
    goto error;

  if (result.length == 0)
    goto error;

  if (escaped) {
    escaped = false;
    length++;
    goto read_character;
  }

  if (character == 92) {
    escaped = true;
    length++;
    goto read_character;
  }

  if (character == '"' && length > 0) {
    length++;
    goto terminate;
  }

  length++;
  goto read_character;

terminate:
  io_cursor_restore(io, cursor);
  return length;

error:
  io_cursor_restore(io, cursor);
  return -1;

  #undef character
}
