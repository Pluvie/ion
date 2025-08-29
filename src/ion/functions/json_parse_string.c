static inline void json<T>_parse_string (
    struct io* io,
    T* source,
    string* result
)
{
  int cursor = io_cursor_save(io);
  bool escaped = false;
  char* data;

  data = io_read(io, source, sizeof(char));
  result->pointer = data;

  if (*data != '"')
    goto error;

read_character:
  data = io_read(io, source, sizeof(char));

  if (escaped) {
    escaped = false;
    goto read_character;
  }

  if (*data == 92) {
    escaped = true;
    goto read_character;
  }

  if (*data == '"')
    goto terminate;

  goto read_character;

terminate:
  result->length = io->cursor - cursor;
  return;

error:
  *result = (string) { 0 };
  io_cursor_restore(io, cursor);
  return;
}
