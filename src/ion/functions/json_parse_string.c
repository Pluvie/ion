static inline int json_parse_string (
    struct io* io
)
{
  int cursor = io_cursor_save(io);
  int length = 0;
  bool escaped = false;
  slice result;
  #define character ((char*) result.data)[0]

read_character:
  result = io_read(io, sizeof(char));
  if (error.occurred)
    goto error;

  if (result.length == 0)
    goto terminate;

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

  if (unlikely(character != '"' && length == 0)) {
    length = 0;
    goto terminate;
  }

  length++;
  goto read_character;

terminate:
  io_cursor_restore(io);
  return length;

error:
  io_cursor_restore(io);
  return -1;

  #undef character
}
