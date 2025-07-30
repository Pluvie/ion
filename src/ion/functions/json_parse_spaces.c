static inline int json_parse_spaces (
    struct io* io
)
{
  int cursor = io_cursor_save(io);
  int length = 0;
  slice result;
  #define character ((char*) result.data)[0]

read_character:
  result = io_read(io, sizeof(char));
  if (error.occurred)
    goto error;

  if (result.length == 0)
    goto terminate;

  if (isspace(character)) {
    length++;
    goto read_character;
  }

terminate:
  io_cursor_restore(io, cursor);
  return length;

error:
  io_cursor_restore(io, cursor);
  return -1;

  #undef character
}
