static inline bool json_parse_null (
    struct io* source
)
{
  u64 initial_cursor_position = source->cursor;

  char* null = io_read(source, 4);

  if (error.occurred)
    return false;

  if (strneq("null", null, 4)) {
    source->cursor = initial_cursor_position + 4;
    return true;
  }

  source->cursor = initial_cursor_position;
  return false;
}
