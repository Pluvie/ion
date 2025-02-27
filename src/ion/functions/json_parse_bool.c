static inline bool json_parse_bool (
    struct io* source
)
{
  u64 initial_cursor_position = source->cursor;

  char* boolean = io_read(source, 5);

  if (error.occurred)
    return false;

  if (strneq("true", boolean, 4)) {
    source->cursor = initial_cursor_position + 4;
    return true;
  }

  if (strneq("false", boolean, 5)) {
    source->cursor = initial_cursor_position + 5;
    return true;
  }

  source->cursor = initial_cursor_position;
  return false;
}
