static inline u64 json_parse_string (
    struct io* source
)
{
  io_cursor_save(source);

  char* character;
  u64 length = 0;
  bool escaped = false;

read_character:
  character = io_read(source, sizeof(char));
  if (error.occurred)
    return 0;

  if (escaped) {
    escaped = false;
    length++;
    goto read_character;
  }

  if (*character == 92) {
    escaped = true;
    length++;
    goto read_character;
  }

  if (*character == '"' && length > 0) {
    length++;
    goto terminate;
  }

  if (unlikely(*character != '"' && length == 0)) {
    length = 0;
    goto terminate;
  }

  length++;
  goto read_character;

terminate:
  io_cursor_restore(source);
  return length;
}
